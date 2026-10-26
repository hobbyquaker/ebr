# ebr case

3D print data for ebr's case: a box for the boards and a lid that carries the display and the four buttons.
Photos in [../images/](../images/).

## Files

| File | What |
| --- | --- |
| `ebr-case.f3d` | the box — Fusion 360 source |
| `ebr-case.stl` | the box — ready to print |
| `ebr-lid.f3d` | the lid with the display window and the button holes — Fusion 360 source |
| `ebr-lid.stl` | the lid — ready to print |

The lid is held by screws in heat-set inserts; the display module is screwed to the lid's back, the buttons sit on
a strip of perfboard behind the button holes.

## What the case has to hold

| Part | Notes |
| --- | --- |
| Waveshare ESP32-P4-ETH | RJ45 Ethernet and the USB-C (power, flashing, console) reachable from outside |
| ESP32-H2 board (ESP32-H2-MINI-1 devkit) | the Thread/Bluetooth antenna: keep it away from the P4 board's ground plane and from metal, no metal parts in front of it |
| 2.0" ST7789 display (GMT020-02-7P, 240×320, used landscape) | window for the active area |
| Four push buttons | under the display, evenly spaced, one under each soft-key cell (left to right BACK, PREV, NEXT, SELECT — see `notes/display-ui.md`) |
| Wiring | P4 ↔ H2 (8 wires), P4 ↔ display (8), P4 ↔ buttons (5) — see `notes/hardware-setup.md` |
