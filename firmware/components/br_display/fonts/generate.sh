#!/usr/bin/env bash
# Regenerates the LVGL bitmap fonts of the display from IBM Plex (SIL Open Font License 1.1, see OFL.txt).
# The generated .c files are committed, so a firmware build needs neither node nor the TTFs.
#
# Usage: generate.sh <dir with the TTFs>
#   IBMPlexSansCondensed-{Regular,SemiBold,Bold}.ttf and IBMPlexMono-{Regular,SemiBold}.ttf from
#   https://github.com/google/fonts/tree/main/ofl/ibmplexsanscondensed and .../ofl/ibmplexmono
set -euo pipefail

ttf_dir=${1:?usage: generate.sh <dir with the TTFs>}
out_dir=$(cd "$(dirname "$0")" && pwd)

# Printable ASCII plus · (U+00B7), – (U+2013), … (U+2026), − (U+2212)
range="0x20-0x7E,0xB7,0x2013,0x2026,0x2212"

gen() { # <name> <ttf> <size>
    npx --yes lv_font_conv@1.5.3 --no-compress --no-prefilter --bpp 4 --format lvgl \
        --font "$ttf_dir/$2" --range "$range" --size "$3" \
        --lv-include lvgl.h --output "$out_dir/$1.c"
}

# Sizes from the design canvas (direction A, 320x240 at 1x)
gen br_font_sans_9       IBMPlexSansCondensed-Regular.ttf   9    # tile labels, footer
gen br_font_sans_11      IBMPlexSansCondensed-Regular.ttf   11   # subtitles, body text
gen br_font_sans_semi_10 IBMPlexSansCondensed-SemiBold.ttf  10   # header bar
gen br_font_sans_semi_12 IBMPlexSansCondensed-SemiBold.ttf  12   # status words in tiles
gen br_font_sans_bold_18 IBMPlexSansCondensed-Bold.ttf      18   # screen titles
gen br_font_sans_bold_26 IBMPlexSansCondensed-Bold.ttf      26   # the role word
gen br_font_mono_9       IBMPlexMono-Regular.ttf            9    # addresses
gen br_font_mono_11      IBMPlexMono-Regular.ttf            11   # table values
gen br_font_mono_semi_14 IBMPlexMono-SemiBold.ttf           14   # tile values
