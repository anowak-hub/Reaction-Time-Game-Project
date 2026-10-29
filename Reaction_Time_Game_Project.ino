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

// Initalize Random Number
long random_num;

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
}

void loop() {
  // Declare Player 1 and Player 2 Digital Reads
  int player1 = digitalRead(2);
  int player2 = digitalRead(3);

  // Game Menu and Initialization
  if (player1 == HIGH && lastP1 == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Player 1 Ready");
  }

  if(player2 == HIGH && lastP2 == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Player 2 Ready");
  }

  // Game Start and Confirmation
  if ((player1 == HIGH && lastP1 == LOW) && (player2 == HIGH && lastP2 == LOW)) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("The Game Will");
    lcd.setCursor(4,1);
    lcd.print("Begin In");
    
    delay(3000);

    for (int i = 5; i > 0; i--) {
      lcd.clear();
      lcd.setCursor(7, 0);
      lcd.print(i);
      delay(1000);
    }

    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Watch/Listen");
    lcd.setCursor(4, 1);
    lcd.print("Carefully");

    // Randomize the LED and Buzzer Output
    random_num = random(3000,10000);

    if (random_num % 2 == 0) {
      delay(random_num);
      digitalWrite(9, HIGH);
    } else {
      delay(random_num);
      digitalWrite(7, HIGH);
    }

    

  }

  lastP1 = player1;
  lastP2 = player2;

  delay(20);
}
