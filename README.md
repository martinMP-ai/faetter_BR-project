# faetter_BR-project

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
├── CMakeLists.txt              # Top-level IDF project file
├── sdkconfig                   # Current build configuration (target = esp32h2)
├── main/
│   ├── CMakeLists.txt          # Component registration
│   └── faetter_BR-project.c    # app_main() with the heartbeat loop
└── .gitignore
```

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
