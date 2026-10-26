#!/usr/bin/env bash
# Renders the display's screens on the workstation, without hardware: compiles LVGL (the version the firmware
# build fetched into managed_components/), br_ui.c and the fonts with the host gcc, and writes one PNG per
# sample state (2x scaled, like the design canvas).
#
# Usage: build.sh [out dir]   — run `idf.py build` (or reconfigure) in firmware/ebr once before, for LVGL.
set -euo pipefail

here=$(cd "$(dirname "$0")" && pwd)
fw=$(cd "$here/../.." && pwd)
lvgl="$fw/ebr/managed_components/lvgl__lvgl"
out=${1:-"$here/out"}
obj="$out/obj"
[ -d "$lvgl/src" ] || { echo "no LVGL in $lvgl — run idf.py reconfigure in $fw/ebr first" >&2; exit 1; }
mkdir -p "$obj"

cflags=(-O1 -w -DLV_CONF_INCLUDE_SIMPLE -I"$here" -I"$here/stubs" -I"$lvgl" -I"$fw/components/br_display/src" -I"$fw/components/br_display/include")

# LVGL once, into a static library
if [ ! -f "$obj/liblvgl.a" ]; then
    mapfile -t srcs < <(find "$lvgl/src" -name '*.c')
    for s in "${srcs[@]}"; do
        o="$obj/lvgl_$(echo "${s#$lvgl/}" | tr '/' '_').o"
        gcc "${cflags[@]}" -c "$s" -o "$o" &
        while [ "$(jobs -rp | wc -l)" -ge "$(nproc)" ]; do wait -n; done
    done
    wait
    ar rcs "$obj/liblvgl.a" "$obj"/lvgl_*.o
fi

gcc "${cflags[@]}" -Wall -o "$obj/preview" "$here/preview.c" "$fw/components/br_display/src/br_ui.c" \
    "$fw"/components/br_display/fonts/*.c "$obj/liblvgl.a" -lm
"$obj/preview" "$out"

# PPM -> PNG at 2x, with the standard library only
python3 -I - "$out" <<'EOF'
import pathlib, struct, sys, zlib
out = pathlib.Path(sys.argv[1])
for ppm in sorted(out.glob('*.ppm')):
    data = ppm.read_bytes()
    parts = data.split(b'\n', 3)
    w, h = map(int, parts[1].split())
    px = parts[3]
    rows = []
    for y in range(h):
        row = px[y * w * 3:(y + 1) * w * 3]
        row2 = b''.join(row[x * 3:x * 3 + 3] * 2 for x in range(w))
        rows += [b'\0' + row2] * 2
    def chunk(t, d):
        return struct.pack('>I', len(d)) + t + d + struct.pack('>I', zlib.crc32(t + d) & 0xffffffff)
    png = b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', w * 2, h * 2, 8, 2, 0, 0, 0)) \
        + chunk(b'IDAT', zlib.compress(b''.join(rows), 9)) + chunk(b'IEND', b'')
    ppm.with_suffix('.png').write_bytes(png)
    ppm.unlink()
    print('png', ppm.with_suffix('.png'))
EOF
