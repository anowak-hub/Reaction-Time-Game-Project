// Psuedocode/Planning
  // Inputs
    // The Buttons
      // Button 1 
        // pinMode(2, INPUT)
        // int player1 = digitalRead(2)
      // Button 2
        // pinMode(3, INPUT)
        // int player2 = digitalRead(3)
    // Outputs 
      // LED 
        // Connected to port 9
      // Active Buzzer 
        // Connected to port 7
      // LCD Display 
        // SDA connected to port SDA 20
        // SCL connected to port SCL 21 


// Libraries 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Initialize LCD 
LiquidCrystal_I2C lcd(0x27, 16, 2);

int lastP1 = LOW;
int lastP2 = LOW;

// Code Implementation
void setup() {
  // Setup for Player 1 and Player 2 
  Serial.begin(9600);
  pinMode(2, INPUT); // Player 1
  pinMode(3, INPUT); // Player 2

  // Setup the LCD Display 
  lcd.init();
  lcd.backlight();
}

void loop() {
  // Declare Player 1 and Player 2 Digital Reads
  int player1 = digitalRead(2);
  int player2 = digitalRead(3);

  if (player1 == HIGH && lastP1 == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Player 1 Works");
  }

  if(player2 == HIGH && lastP2 == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Player 2 Works");
  }

  lastP1 = player1;
  lastP2 = player2;

  delay(20);
}
