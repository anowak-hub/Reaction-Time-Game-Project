# Reaction Time Testing Game

**Course:** PHY 306, Elmhurst University
**Professor:** Halliday
**Authors:** Andrew and Kevin
**Proposal Date:** 10.15.2026

## Project Description

A mechatronics project that tests and compares player reaction times. The LCD explains the game, the player waits a random amount of time, and an LED or buzzer signals the start. The player presses their button as fast as possible. The faster the reaction, the more points they score. Two buttons allow head-to-head play, where the first valid press wins the round.

## Goals

- Display game instructions and results on a 16x2 I2C LCD
- Use a randomized delay before the LED or buzzer signal so players can't predict it
- Measure reaction time in milliseconds from the signal to the button press
- Detect false starts (pressing before the signal)
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

- [x] **LCD communication:** The I2C LCD initializes and displays text.
- [x] **Button input:** Both buttons are read on pins 2 and 3.
- [x] **Press detection:** Detecting the moment of the press (LOW to HIGH) instead of the held state keeps the message on the LCD after the button is released.
- [x] **Two-line output:** `setCursor(column, row)` places text on each line.
- [x] **Centered text:** A `printCentered()` helper centers messages using `(16 - length) / 2`.
- [x] **LED signal on pin 9**
- [x] **Buzzer feedback on pin 7**
- [x] **Randomized delay** before the LED or buzzer turns on (`random(3000, 10000)`)
- [x] Reaction time measurement (`millis()`)

### Issues Found and Fixed

| Issue | Cause | Fix |
|---|---|---|
| Message only showed while the button was held | The loop cleared and redrew the LCD every cycle | Update the LCD only on a detected press |
| Nothing displayed after the first fix | A leftover `lcd.clear()` at the top of `loop()` erased the message every 20 ms | Removed the extra `lcd.clear()` |
| Text not printing correctly | `lcd.println()` was used | Switched to `lcd.print()` |
| Pressing a button after a signal looped back to the "Ready" message instead of recording a time | Button values were read once at the top of `loop()` and never refreshed inside the game block | Re-read the buttons continuously after the signal turns on |
| Game never started | The start condition required both buttons to be pressed within the same 20 ms loop pass | Track each player's ready state with `p1Ready` / `p2Ready` flags |
| Reaction time displayed as garbage text | `"Player 1: " + reaction_time` adds a number to a string pointer in C++ | Print the label and the number with separate `lcd.print()` calls |

### Still To Test

- [ ] False-start detection
- [ ] Two-player winner logic
- [ ] Best time tracking and five-round average
- [ ] Full end-to-end game run

## Repository Contents

- `/` Arduino sketch(es) for the game
- `README.md` Project overview and testing log

## Authors

Andrew and Kevin, PHY 306, Elmhurst University
