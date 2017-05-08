/*
 Simple serial (nessun fine riga)
*/

int led = 13; // Pin 13

void setup()
 {
     pinMode(led, OUTPUT); // Set pin 13 as digital out

    // Start up serial connection
    Serial.begin(9600); // baud rate
    Serial.flush();
}

void loop()
{
    String input = "";

    // Read any serial input
    while (Serial.available() > 0)
    {
        input += (char) Serial.read(); // Read in one char at a time
        delay(5); // Delay for 5 ms so the next char has time to be received
    }

    if (input == "o")
    {
        digitalWrite(led, HIGH); // on
    }
    else if (input == "f")
    {
        digitalWrite(led, LOW); // off
          }
}
