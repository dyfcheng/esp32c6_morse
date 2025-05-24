# Changelog – esp32c6_morse

## [1.0.0] – 2025-05-22

### Added
- Initial project structure supporting ESP32-C6 LCD board.
- Morse code blinking via onboard RGB LED.
- Serial UART input to accept user strings.
- LCD display of string with 8x8 font rendering.
- Modularized code into `main.c`, `morse_blinker.[ch]`, and `font8x8_renderer.[ch]`.
- Basic ASCII font set including A-Z, space, common punctuations (!, ., ,).
- ASCII to Morse code translation, with unknown characters treated as space.

### Changed
- Moved `init_led_strip()` from `main.c` to `morse_blinker.c`.
- Moved `init_lcd()` from `main.c` to `font8x8_renderer.c`.
- Removed deprecated or misused Kconfig options from `sdkconfig.defaults`.
- Updated CMake files to clearly reflect module ownership.

### Fixed
- Overwritten array initializer in `font8x8_basic[]`.
- Linker and compiler errors related to missing includes, symbol mismatches, and build inconsistencies.

### Known Limitations
- Morse renderer ignores unsupported characters silently.
- Font rendering is bitmap-based and not highly optimized.
- No scrolling support yet for long messages.
