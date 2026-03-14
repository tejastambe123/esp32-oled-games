# 🎮 ESP32 OLED Games

Two classic arcade games built from scratch using an ESP32 microcontroller,
a 0.96" OLED display, a joystick, and LEDs — all on a breadboard.
---
## Games
### 🐍 Snake
Control a growing snake using the joystick. Eat food to grow longer and
increase your score. Hit yourself and it's game over. The snake wraps
around the edges so there are no walls to worry about.

### 🧱 Brick Breaker
Move the paddle left and right to bounce a ball and break all the bricks.
You have 3 lives. Break all 24 bricks to win. The angle of the ball changes
depending on where it hits the paddle. Score is shown live on the 4-digit
TM1637 display.
---
## Hardware Required

| Component | Details |
|-----------|---------|
| ESP32 | Dev board (ESP32-D0WDQ6 or similar) |
| OLED Display | 0.96 inch SSD1306, I2C (GND VDD SCK SDA) |
| Joystick Module | Analog XY + button (GND +5V VRx VRy SW) |
| TM1637 Display | 4-digit 7-segment, V1.2 (CLK GND DIO VCC) |
| Green LED | With 220Ω resistor |
| Red LED | With 220Ω resistor |
| Breadboard | Full size recommended |
| Jumper wires | Male to male |
| USB cable | Data capable (not charge only) |

---

## Wiring

### OLED (I2C) → ESP32
| OLED | ESP32 |
|------|-------|
| VDD | 3V3 |
| GND | GND |
| SCK | GPIO22 |
| SDA | GPIO21 |

### Joystick → ESP32
| Joystick | ESP32 |
|----------|-------|
| +5V | 3V3 |
| GND | GND |
| VRx | GPIO34 |
| VRy | GPIO35 |
| SW | GPIO15 |

### TM1637 → ESP32 (Brick Breaker only)
| TM1637 | ESP32 |
|--------|-------|
| VCC | 3V3 |
| GND | GND |
| CLK | GPIO13 |
| DIO | GPIO12 |

### LEDs → ESP32
| Component | ESP32 | Note |
|-----------|-------|------|
| Green LED (+) | GPIO26 | 220Ω resistor in series |
| Red LED (+) | GPIO27 | 220Ω resistor in series |
| Both LED (-) | GND | Common ground |

> All modules run on 3.3V. Do not connect anything to 5V —
> the ESP32 ADC pins maximum is 3.3V.

---

## Libraries Required

Install all three via Arduino IDE:
**Sketch → Include Library → Manage Libraries**

| Library | Author | Used for |
|---------|--------|----------|
| Adafruit SSD1306 | Adafruit | OLED display |
| Adafruit GFX Library | Adafruit | Graphics drawing |
| TM1637 | Avishay Orpaz | 4-digit score display |

---

## Arduino IDE Settings

| Setting | Value |
|---------|-------|
| Board | ESP32 Dev Module |
| Upload Speed | 115200 |
| Port | Your COM port |

---

## How to Upload

1. Open the `.ino` file in Arduino IDE
2. Select the correct board and port under **Tools**
3. Click **Upload**
4. If you see `Connecting....` hold the **BOOT button** on the ESP32
5. Release once uploading starts

---
## How to Play

### Snake
- Tilt joystick in any direction to move the snake
- Eat the food (small X on screen) to grow
- Score shown top right on OLED
- Green LED flashes when you eat food
- Red LED lights up on game over
- Tilt joystick to restart after game over

### Brick Breaker
- Tilt joystick left and right to move the paddle
- Bounce the ball to break all bricks
- Hit left edge of paddle = ball goes left
- Hit right edge of paddle = ball goes right
- Score shown live on TM1637 display
- Green LED flashes on every brick hit
- Red LED flashes when you lose a life
- Press joystick button to restart after game over
- Break all 24 bricks to win

---

## Project Structure
```
esp32-oled-games/
├── snake_game/
│   └── snake_game.ino
├── brick_breaker/
│   └── brick_breaker.ino
└── README.md
```
## Built With

- ESP32 Arduino Core
- Adafruit SSD1306 + GFX libraries
- TM1637 library by Avishay Orpaz
---
## Author

Made with a breadboard, some jumper wires, and a lot of fun.
Feel free to fork, improve, and share!
