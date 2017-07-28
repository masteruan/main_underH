int valvole = 1;
int danger= 2;
int mano = 3;
int motore= 4;
int croce= 5;

boolean H_valvole = false ;
boolean H_generatore = false ;
boolean H_motore = false;

// serial
boolean stringComplete = false;
String input = ""; //String
char inChar;

typedef struct {
  String str;
  int pin;
}
output;
output outputs[5]={
  {"valvole", valvole},
  {"danger", danger},
  {"mano", mano},
  {"motore", motore},
  {"croce", croce}, //default 26
  };


typedef struct {
  String stri;
  boolean OK;
}
ok;
ok okHints[3]={
  {"OK_valvole", H_valvole},
  {"OK_generatore", H_generatore},
  {"OK_motore", H_motore},
  };

void setup() {
  Serial.begin(9600);
  for (int i = 0; i <4; i++) {
    Serial.println(okHints[i].stri);
  }
  Serial.print(H_motore);
}

void loop() {
  if (stringComplete) {
    //Serial.println(input);
    seriale();
    input = "";
    stringComplete = false;
  }
 // game();
  //lettura();

}

void seriale() {
  int state;
  //quello che c'è prima della virgola compresa la virgola
  int index = input.indexOf(',');
  int pin;
  int numA;
  int numB;
  boolean buleano;
  if(index != -1){
    
    for (int i=0; i < 4; i++){
      if (input.substring(0, index) == okHints[i].stri){
        okHints[i].OK = true;
        buleano = okHints[i].OK;
        numB = i;
      }
    }
    for (int k = 0; k < 6; k++){
      if (input.substring(0, index) == outputs[k].str){
        pin = outputs[k].pin;
        numA = k;
        state = (input.substring(index+1,index+2)).toInt();
      }
    }
    
  }
  // debug
  Serial.print(outputs[numA].str);
  Serial.print(" Numero pin: ");
  Serial.println(pin);
  Serial.print("Stato: ");
  Serial.println(state);
  
  Serial.print(okHints[numB].stri);
  Serial.print(" stato: ");
  Serial.println(buleano);

  okHints[numB].OK = true;
  Serial.print(H_motore);
}

void serialEvent() {
  Serial.flush();
  //Serial.begin(9600);
  delay(20);
  // Read any serial input
  while (Serial.available())
  {
    inChar = (char)Serial.read(); // Read in one char at a time
    input += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
