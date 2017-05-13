/*
 Main sottoterra
 13 Maggio 2017
*/
int lang;
int led = 13; // Pin 13
String input = "";
char inChar ;

void setup()
 {
    pinMode(led, OUTPUT); // Set pin 13 as digital out
    // Start up serial connection
    Serial.begin(9600); // baud rate
    Serial.flush();
}

void loop()
{
seriale();
}

void seriale() {
  // Read any serial input
  while (Serial.available())
  {
      inChar = (char)Serial.read(); // Read in one char at a time
      input += inChar;
  }

  // test serial
  if (input == 'o')
  {
      digitalWrite(led, HIGH);
  }
  else if (input == 'f')
  {
      digitalWrite(led, LOW);
  }
}
