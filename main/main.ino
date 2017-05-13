/*
 Simple serial (nessun fine riga)
*/

int led = 13; // Pin 13

    char inChar = "";
    String input;

void setup()
 {
     pinMode(led, OUTPUT); // Set pin 13 as digital out

    // Start up serial connection
    Serial.begin(9600); // baud rate
    Serial.flush();
}

void loop()
{
    // Read any serial input
    while (Serial.available())
    {
        //char inChar = (char) Serial.read(); 
        //input += inChar;
        if (inChar == '\n') {
          boolean stringComplete= true;
        }
    }

    if (input == "y")
    {
        digitalWrite(led, HIGH); // on
    }
    if (input == "000")
    {
        digitalWrite(led, LOW); // off
    }
}

void 
