# faetter_BR-project

[![Build](https://github.com/martinMP-ai/faetter_BR-project/actions/workflows/build.yml/badge.svg)](https://github.com/martinMP-ai/faetter_BR-project/actions/workflows/build.yml)

A minimal ESP-IDF firmware for the **ESP32-H2** that prints a 1 Hz heartbeat log
over the USB-Serial-JTAG console. It's intended as a known-good starter that
verifies your ESP-IDF toolchain, board, and flashing workflow end-to-end.

## Requirements

- [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32h2/get-started/) v5.1 or later (tested on v6.1-dev)
- An ESP32-H2 board (e.g. ESP32-H2-DevKitM-1)
- USB-C cable and a host with a working Python 3.10+ environment
- macOS, Linux, or Windows host

## Getting started

### 1. Set up the ESP-IDF environment

From the directory where you cloned / unpacked ESP-IDF:

```bash
. $HOME/esp-idf/export.sh
```

(Adjust the path if your IDF install lives elsewhere.)

### 2. Configure, build, flash, and monitor

```bash
idf.py set-target esp32h2
idf.py build
idf.py flash
idf.py monitor
```

Exit the monitor with `Ctrl+]`. Combine steps via `idf.py flash monitor`.

### 3. Expected output

After a clean power-on boot (no `USB_BOOT` latch), you should see:

```
I (xxx) faetter_BR: Application started on ESP32-H2
I (xxx) faetter_BR: Heartbeat #0
I (xxx) faetter_BR: Heartbeat #1
I (xxx) faetter_BR: Heartbeat #2
...
```

## Project layout

```
faetter_BR-project/
├── CMakeLists.txt                      # Top-level IDF project file
├── sdkconfig                           # Build configuration (target = esp32h2)
├── main/
│   ├── CMakeLists.txt
│   └── faetter_BR-project.c            # app_main() heartbeat loop
├── components/
│   └── counter/                        # Tiny reusable counter component
│       ├── CMakeLists.txt
│       ├── counter.c
│       ├── include/counter.h
│       └── test/                       # Unity test cases for counter
│           ├── CMakeLists.txt
│           └── test_counter.c
├── test_app/                           # Dedicated IDF project that runs Unity tests
│   ├── CMakeLists.txt
│   └── main/
│       ├── CMakeLists.txt
│       └── test_app_main.c
└── .github/workflows/build.yml         # CI: firmware build + host-target tests
```

## Running tests

Unit tests live next to each component under `components/<name>/test/` and are
driven by the Unity framework. A dedicated project in `test_app/` discovers
and runs every registered `TEST_CASE()`. Tests can run either on a real chip
or on the `linux` host target (the approach used in CI, no hardware needed).

### On the Linux host (no hardware)

```bash
cd test_app
idf.py --preview set-target linux
idf.py build
./build/faetter_BR-project-tests.elf
```

Exit code is `0` on success, non-zero if any test case fails.

### On an ESP32-H2 board

```bash
cd test_app
idf.py set-target esp32h2
idf.py flash monitor
```

The runner prints the Unity summary (`N Tests 0 Failures 0 Ignored`) at the
end and then idles; exit the monitor with `Ctrl+]`.

## Troubleshooting

### Board stuck at `wait usb download`

If the monitor repeatedly prints:

```
rst:0x15 (USB_UART_HPSYS),boot:0x0 (USB_BOOT)
wait usb download
```

...the chip's boot strapping pin (GPIO9 on ESP32-H2) was held LOW at reset and
the ROM is waiting for a USB download instead of running the flashed firmware.

Fixes:

1. **Unplug the USB cable, wait ~2 seconds, plug it back in.** Do not hold the
   BOOT button.
2. Tap the board's **RESET** button.
3. Verify the BOOT button isn't mechanically stuck.

### Port busy / resource temporarily unavailable

A previous `idf.py monitor` or `esptool` session may still be attached. Find
and kill it:

```bash
lsof /dev/cu.usbmodem101
kill <PID>
```

## Licensing

See individual source files for license headers. Project code is provided as-is.
