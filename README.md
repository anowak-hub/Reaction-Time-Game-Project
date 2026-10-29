# Reaction Time Testing Game

**Course:** PHY 306, Elmhurst University
**Professor:** Halliday
**Authors:** Andrew and Kevin
**Proposal Date:** 10.15.2026

## Project Description

A mechatronics project that tests and compares player reaction times. The LCD explains the game, the player waits a random amount of time, and an LED lights up as the signal. The player presses their button as fast as possible. The faster the reaction, the more points they score. Two buttons allow head-to-head play, where the first valid press wins the round.

## Goals

- Display game instructions and results on a 16x2 I2C LCD
- Use a randomized delay before the LED signal so players can't predict it
- Measure reaction time in milliseconds from the LED signal to the button press
- Detect false starts (pressing before the LED turns on)
- Support two-player mode with winner determination
- Track each player's best time and a five-round average
- Give audio feedback with a buzzer

## Hardware

| Component | Qty | Connection |
|---|---|---|
| SunFounder Mega board | 1 | USB to computer |
| 16x2 LCD (I2C, address `0x27`) | 1 | SDA to pin 20, SCL to pin 21 |
| Push button (Player 1) | 1 | Digital pin 2 |
| Push button (Player 2) | 1 | Digital pin 3 |
| LED | 1 | Digital pin 9 |
| Active buzzer | 1 | Digital pin 7 |
| Resistors | 3 | Button and LED circuits |
| Potentiometer | 1 | LCD contrast, if required |
| Breadboard and wires | 1 set | n/a |

**Estimated cost:** $0 to $10. Most parts are available in the classroom.

## Software

- Arduino IDE
- Libraries: `Wire.h`, `LiquidCrystal_I2C.h`

## Task Flow and Estimated Effort

| Task | Time |
|---|---|
| Research similar games and determine requirements | ~1 hr |
| Plan circuit connections and test individual components | ~1 hr |
| Build the breadboard circuit (LCD, buttons, LED, buzzer) | ~1.5 hr |
| Program random timing, reaction measurement, false-start detection | ~2 hr |
| Implement two-player winner, best times, five-round averages | ~1.5 hr |
| Integrate LCD and buzzer feedback; debug hardware and software | ~1 hr |
| Final testing and documentation | ~0.5 hr |
| **Total estimated NRE** | **8.5 hr** |

*NRE (Non-Recurring Engineering) is the one-time research, design, programming, construction, integration, and debugging effort required to develop the project.*

## Testing Progress (as of now)

### Completed

- **LCD communication:** The I2C LCD initializes and displays text.
- **Button input:** Both buttons are read on pins 2 and 3.
- **Press detection:** Detecting the moment of the press (LOW to HIGH) instead of the held state keeps the message on the LCD after the button is released.
- **Two-line output:** `setCursor(column, row)` places text on each line.
- **Centered text:** A `printCentered()` helper centers messages using `(16 - length) / 2`.

### Issues Found and Fixed

| Issue | Cause | Fix |
|---|---|---|
| Message only showed while the button was held | The loop cleared and redrew the LCD every cycle | Update the LCD only on a detected press |
| Nothing displayed after the first fix | A leftover `lcd.clear()` at the top of `loop()` erased the message every 20 ms | Removed the extra `lcd.clear()` |
| Text not printing correctly | `lcd.println()` was used | Switched to `lcd.print()` |

### Current Test Sketch (button to LCD)

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int lastP1 = LOW;
int lastP2 = LOW;

void printCentered(const char* text, int row) {
  int col = (16 - strlen(text)) / 2;
  if (col < 0) col = 0;
  lcd.setCursor(col, row);
  lcd.print(text);
}

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT); // Player 1
  pinMode(3, INPUT); // Player 2
  lcd.init();
  lcd.backlight();
}

void loop() {
  int player1 = digitalRead(2);
  int player2 = digitalRead(3);

  if (player1 == HIGH && lastP1 == LOW) {
    lcd.clear();
    printCentered("Player 1", 0);
    printCentered("Wins!", 1);
  }

  if (player2 == HIGH && lastP2 == LOW) {
    lcd.clear();
    printCentered("Player 2", 0);
    printCentered("Wins!", 1);
  }

  lastP1 = player1;
  lastP2 = player2;
  delay(20); // short delay also helps debounce
}
```

### Still To Test

- [x] LED signal on pin 9
- [x] Buzzer feedback on pin 7
- [x] Randomized delay before the LED or Buzzer turns on
- [ ] Reaction time measurement (`millis()`)
- [ ] False-start detection
- [ ] Two-player winner logic
- [ ] Best time tracking and five-round average
- [ ] Full end-to-end game run

## Repository Contents

- `/` Arduino sketch(es) for the game
- `README.md` Project overview and testing log

## Authors

Andrew and Kevin, PHY 306, Elmhurst University
