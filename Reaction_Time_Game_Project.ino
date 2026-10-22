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

void setup() {
  // Setup for Player 1 and Player 2 
  Serial.begin(9600);
  pinMode(2, INPUT); // Player 1
  pinMode(3, INPUT); // Player 2

}

void loop() {
  // Declare Player 1 and Player 2 Digital Reads
  int player1 = digitalRead(2);
  int player2 = digitalRead(3);

  if (player1 == HIGH) {
    Serial.println("Player 1 Works");
  }

  if(player2 == HIGH) {
    Serial.println("Player 2 Works");
  }
  
  delay(1);
}
