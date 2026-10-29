// Libraries 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Initialize LCD 
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Initialize Players and Their Ready State
int lastP1 = LOW;
int lastP2 = LOW;

bool p1Ready = false;
bool p2Ready = false;

// Initalize the Random Number and Start Time for when the game begins
long random_num;

unsigned long start_time;

// Code Implementation
void setup() {
  // Setup for Player 1 and Player 2 
  Serial.begin(9600);
  pinMode(2, INPUT); // Player 1
  pinMode(3, INPUT); // Player 2

  // Setup the LCD Display 
  lcd.init();
  lcd.backlight();

  // Setup the Random Seed
  randomSeed(analogRead(0));

  // Setup the LED Light
  pinMode(9, OUTPUT);

  // Setup the Active Buzzer
  pinMode(7, OUTPUT);

  // Show Ready Screen
  showReadyScreen();
}

void loop() {
  int player1 = digitalRead(2);
  int player2 = digitalRead(3);

  // Ready Up 
  if (player1 == HIGH && lastP1 == LOW) p1Ready = true;
  if (player2 == HIGH && lastP2 == LOW) p2Ready = true;

  if (p1Ready || p2Ready) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(p1Ready ? "P1 Ready" : "P1 Waiting");
    lcd.setCursor(0, 1);
    lcd.print(p2Ready ? "P2 Ready" : "P2 Waiting");
  }

  // Round Start 
  if (p1Ready && p2Ready) {
    playRound();
    p1Ready = false;
    p2Ready = false;
    showReadyScreen();
  }

  lastP1 = player1;
  lastP2 = player2;
  delay(20);
}

// Function that Shows the Ready Screen/Start Screen
void showReadyScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Both Players");
  lcd.setCursor(0, 1);
  lcd.print("Press to Start");
}

// Function that Plays the Round
void playRound() {
  while (digitalRead(2) == HIGH || digitalRead(3) == HIGH) {}

  // Round Countdown
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("The Game Will");
  lcd.setCursor(4, 1);
  lcd.print("Begin In");
  delay(2000);

  for (int i = 5; i > 0; i--) {
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print(i);
    delay(1000);
  }

  // Game is now currently going
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Watch/Listen");
  lcd.setCursor(4, 1);
  lcd.print("Carefully");

  // Randomize the LED or Buzzer activation, and randomize the time activation starts
  delay(random(3000,10000));

  if (random(2) == 0) digitalWrite(9, HIGH);
  else digitalWrite(7, HIGH);

  unsigned long start = millis();
  unsigned long t1 = 0, t2 = 0;

  // Keep Track of Player Reaction Time
  while ((t1 == 0 || t2 == 0) && millis() - start < 3000) {
    if (t1 == 0 && digitalRead(2) == HIGH) t1 = millis() - start;
    if (t2 == 0 && digitalRead(3) == HIGH) t2 = millis() - start;
  }

  digitalWrite(9, LOW);
  digitalWrite(7, LOW);

  // Record Results
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("P1: ");
  if (t1 > 0) { lcd.print(t1); lcd.print(" ms"); } else lcd.print("--");
  lcd.setCursor(0, 1);
  lcd.print("P2: ");
  if (t2 > 0) { lcd.print(t2); lcd.print(" ms"); } else lcd.print("--");

  delay(5000);
}
