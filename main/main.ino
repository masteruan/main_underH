/*
 Main sottoterra
 12 Giugno 2017
 Spezzato
 
OUTPUT
Candele 29 -- M4  46
Timone 28  -- M5  47
Monaco 27  -- M6  48
Croce 35   -- M7  49
Motore 25  -- M8  50
Mano 24    -- M9  51
Danger 23  -- M10 52
Valvole 22 -- M11 53
--         --
Organo 37         --  Pulsanti  38
Orologi 36        --  Organo play 39
Ventilatore 35    --  Nano 40
Timone (segle) 34 --  Libero 41
Stereo 33         --  Libero 42
Foto 32           --  M1 43
Culla (gira) 31   --  M2 44
Culla 30          --  M3 45
--                --
RELAY PICCOLI
audio
ralay1 4  --  relay3 3
relay2 5  --  relay4 2
RELAY 220 V
luci
luce_terzo 11(Sala Grande)|luce_quarto 12(Ingresso)
luce_secondo 10(Uscita)|luce_primo 9(primo piano)
INPUT
Timone A11  --  Libero A10
Organo A9   --  Orologi A8
Culla A7    --  Stereo A6
Foto A5     --  Start A4
Croce A2    --  Interruttori A3
Motore A1   --  Valvole A0
Instructions
Send to serial
"_preparation" to close all the doors and switch on all the lights
"_startGame" to start the game
"_secondFloor" to switch on the second floor
"_vent" for the animation of ventilator
"_nano" for the animation of dwarf
*/

// Libraries
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "variables.h"

SoftwareSerial mySoftwareSerial(6, 7); // RX, TX
DFRobotDFPlayerMini myDFPlayer;


void setup()
 {
   Serial.flush();
   // OUTPUT
   for (int i = 22; i < 54; i++){
     pinMode(i,OUTPUT);
   }
   for (int i = 2; i < 6; i++){
     pinMode(i, OUTPUT);
   }
    pinMode(led, OUTPUT); // Set pin 13 as digital out
  for (int i = 9; i < 14; i++){
    pinMode(i, OUTPUT);
  }
    // INPUT
    // This input give FALSE if the input is open TRUE if the input is closed
    for (int i = 0; i < 13; i++){
      pinMode(games[i], INPUT_PULLUP);
    }

    // Start up serial connection
    mySoftwareSerial.begin(115200); //default 9600
    Serial.begin(9600); //default 115200
    input.reserve(200);

    // Start mp3 player
    if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
      Serial.println(F("Unable to begin:"));
      Serial.println(F("1.Please recheck the connection!"));
      Serial.println(F("2.Please insert the SD card!"));
      //while(true);
    }
    myDFPlayer.volume(30); // min = 0 max = 30
    myDFPlayer.loop(1);

    Serial.println("################");
    Serial.println("You are Welcome!");
}

void loop()
{
  if (stringComplete) {
    Serial.println(input);
    seriale();
    input = "";
    stringComplete = false;
  }
game();
}

void game () {

  if (start_game){

    // reset booleane
    read_valvole = false;
    OK_valvole = false;
    read_motore = false;
    OK_motore = false;
    OK_generatore = false;
    read_interruttori = false;
    OK_interruttori = false;
    read_croce = false;
    OK_secondFloor = false;
    OK_croce = false;
    read_foto = false;
    OK_foto = false;
    read_stereo = false;
    OK_stereo = false;
    read_culla = false;
    OK_culla = false;
    read_orologi = false;
    OK_orologi = false;
    read_organo = false;
    OK_organo = false;
    read_timone = false;
    OK_timone = false;

    // chiudi tutte le elettrocalamite
    for(int i= 0; i<54; i++){
      digitalWrite(i,LOW);
    }
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
    digitalWrite(M3, HIGH);
    digitalWrite(M4, HIGH);
    digitalWrite(M5, HIGH);
    digitalWrite(M6, HIGH);
    digitalWrite(M8, HIGH);
    digitalWrite(M9, HIGH);
    digitalWrite(M10, HIGH);
    digitalWrite(M11, LOW);
    digitalWrite(croce, HIGH);
    // accendi i primi giochi
    digitalWrite(valvole, HIGH);
    start_game = false;
    game_started = true;
    digitalWrite(luce_terzo,LOW);
  }
  else if (game_started){
  sign_valvole = digitalRead(in_valvole);
  if (!sign_valvole && !OK_valvole){
    digitalWrite(danger, HIGH); // switch off "DANGER"

    digitalWrite(motore, HIGH); // switch on motor

    digitalWrite(M1, LOW); // open the door
    Serial.println("\nOK Valvole");
    OK_valvole = true;
  }
  delay(10);
  if(OK_valvole){
    sign_generatore = digitalRead(in_generatore);
  }
  if (sign_generatore && !OK_generatore){
    digitalWrite(luce_quarto, HIGH);
    //digitalWrite(luce_terzo, HIGH); //sala grande
    Serial.println("\nOK Generatore");
    OK_generatore = true;
  }
  if(OK_generatore){
    sign_motore = digitalRead(in_motore);
  }
  if (!sign_motore && !OK_motore){
    digitalWrite(M2, LOW); // open the door
    digitalWrite(M11, LOW);
    delay(2000);
    //digitalWrite(luce_terzo, LOW);
    //digitalWrite(luce_quarto, LOW);
    digitalWrite(monaco, HIGH);
    Serial.println("\nOK motore");
    OK_motore = true;
  }

  // if the players are on the second floor
  if (second_floor && !OK_secondFloor){
    digitalWrite(M11, HIGH); //cella croce
    delay(200);
    digitalWrite(monaco, LOW);
    digitalWrite(candele, HIGH);
    digitalWrite(M6, LOW);
    OK_secondFloor = true;
    // ###############################LAVORA!!
    //    digitalWrite(M6, LOW); JAVA
    // M6 HIGH
    // M4 LOW
    // luce primo low
    }

  // waiting for operator "_vent" & off tutti i caschi
  // waiting for operator unlock the BIG BOX (JOHN JAVA) _scatolaGrande
  if (OK_secondFloor){
    sign_croce = digitalRead(in_croce);
  }
  if (!sign_croce && !OK_croce){
    digitalWrite(M7, HIGH); //sblocca scatola piccola
    delay(20);
    digitalWrite(M11, LOW); //cella della croce
    delay(20);
    digitalWrite(foto, HIGH);
    Serial.println("\nOK croce");
    OK_croce = true;
  }
  if(OK_croce) {
    sign_foto = digitalRead(in_foto);
  }
  if (!sign_foto && !OK_foto){
    digitalWrite(stereo, HIGH);
    delay(3000);
    digitalWrite(culla, HIGH); // accende la culla
    delay(20);
    Serial.println("\nOK foto");
    OK_foto = true;
  }
  if(OK_foto) {
    sign_stereo = digitalRead(in_stereo);
  }
  if (!sign_stereo && !OK_stereo){
    digitalWrite(culla, LOW);
    delay(4000);
    digitalWrite(stereo, LOW);
    delay(1000);
    digitalWrite(culla, HIGH);
    Serial.println("\nOK stereo");
    OK_stereo = true;
  }
  if(OK_stereo) {
    sign_culla = digitalRead(in_culla);
  }
  if (!sign_culla && !OK_culla){
    digitalWrite(M10, LOW); // sblocca cella timone
    delay(50);
    digitalWrite(timone, HIGH);
    digitalWrite(M7, LOW); //rilascia la calamita scatola piccola
    Serial.println("\nOK culla");
    OK_culla = true;
  }
  if(OK_culla){
    sign_timone = digitalRead(in_timone);
  }
  if (!sign_timone && !OK_timone) {
    digitalWrite(M9, LOW); //sblocca la porta per gli orologi
    digitalWrite(orologi, HIGH);
    Serial.println("\nOK timone");
    OK_timone = true;
  }
  if(OK_timone){
    sign_orologi = digitalRead(in_orologi);
  }
  if (!sign_orologi && !OK_orologi) {
    digitalWrite(M5, LOW);// apre porta per il nano
    //digitalWrite(luce_primo, HIGH);
    delay(6000);
    digitalWrite(nano, HIGH);
    delay(100);
    digitalWrite(organo, HIGH);
    delay(200);
    digitalWrite(pulsanti, HIGH);
    Serial.println("\nOK orologi");
    OK_orologi = true;
  }
  if(OK_orologi){
    sign_organo = digitalRead(in_interruttori);
  }
  if (!sign_organo && !OK_organo) {
    digitalWrite(nano,LOW);
    digitalWrite(luce_primo,LOW);
    digitalWrite(luce_secondo, HIGH); // accendi la luce finale
    delay(10000);
    digitalWrite(mano, HIGH);
    Serial.println("\nOK organo\nFinish Game!");
    OK_organo = true;
  }
  if(OK_organo){

  }
/*
  sign_start = digitalRead(in_start);
  if (!read_start && !sign_start){
    start_game = true;
    read_start = true;
    sign_start = true;
  }
  */
  }
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
