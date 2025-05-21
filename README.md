# ESP32C6 Morse Code Blinker with RGB LED and LCD

This is a sample project for the **ESP32-C6** microcontroller that simulates Morse code using an onboard **RGB LED** and optionally displays text on an **ST7789 SPI LCD**. The message "HELLO" is translated into Morse (`.... . .-.. .-.. ---`) and blinked repeatedly.

---

## 🔧 Features

- ✅ Morse code simulation with RGB LED (WS2812, GPIO 8)
- ✅ Optional text display on ST7789 172x320 LCD
- ✅ ESP-IDF v5.4.1 compatible
- ✅ Clean FreeRTOS-based architecture
- ✅ Console output of DOTs and DASHes
- ✅ Configurable message buffer

---

## 📦 Project Structure

```
esp32c6_morse/
├── CMakeLists.txt
├── sdkconfig.defaults
├── esp32c6_morse_project.txt
├── README.md ← (this file)
└── main/
    ├── main.c
    └── CMakeLists.txt
```

---

## 📲 How to Use

### 1. Prerequisites

- ESP-IDF v5.4.1 properly installed and configured
- ESP32-C6 board connected via USB
- Port identified (e.g. `COM4` on Windows)

### 2. Set Target and Build

```bash
idf.py set-target esp32c6
idf.py build
```

### 3. Flash and Monitor

```bash
idf.py -p COM4 flash monitor
```

You should see console output and observe the RGB LED blinking Morse code.

---

## 💡 Hardware Configuration

- RGB LED (WS2812) is hardwired to **GPIO 8**
- SPI LCD (optional) pins:
  - MOSI: GPIO 6
  - CLK: GPIO 7
  - CS: GPIO 14
  - DC: GPIO 15
  - RST: GPIO 21

---

## ⚠️ Notes

- Text display on the LCD is enabled, but optional.
- Make sure to run `idf.py fullclean` before switching targets.
- You can change the message from `"HELLO"` to any Morse-compatible text inside `main.c`.

---

## 📜 License

MIT License. See `LICENSE` file if added.

---

## 👤 Author

Created and maintained by [Daniel Cheng](https://github.com/yourusername)

Contributions welcome!
