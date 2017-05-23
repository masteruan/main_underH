/*
 Main sottoterra
 15 Maggio 2017

OUTPUT
Candele 29 -- M4  46
Timone 28  -- M5  47
Monaco 27  -- M6  48
Croce 26   -- M7  49
Motore 25  -- M8  50
Mano 24    -- M9  51
Danger 23  -- M10 52
Valvole 22 -- Libero 53
--         --
Organo 37         --  Pulsanti  38
Orologi 36        --  Organo play 39
Ventilatore 35    --  Nano 40
Timone (segle) 34 --  Luce generale 41
Stereo 33         --  Luce sala gr. 42
Foto 32           --  M1 43
Culla (gira) 31   --  M2 44
Culla 30          --  M3 45
--                --
RELAY PICCOLI
audio
ralay1 4  --  relay3 3
relay2 5  --  relay4 2

INPUT
Timone A11  --  Libero A10
Organo A9   --  Orologi A8
Culla A7    --  Stereo A6
Foto A5     --  Start A4
Croce A2    --  Interruttori A3
Motore A1   --  Valvole A0


Instructions
Send to serial 'start_game' to start the game.

*/

// Libraries
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(6, 7); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// Variables
int lang;
int led = 13; // Pin 13

// switch
boolean start_game = false;
boolean second_floor = false;

// serial
boolean stringComplete = false;
String input = ""; //String
char inChar ;

// input Variables
int games[] = {A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11};

int in_valvole = A0;
boolean sign_valvole = true;
boolean read_valvole = false;

int in_motore = A1;
boolean sign_motore = true;
boolean read_motore = false;

int in_interruttori = A3;
boolean sign_interuttori = true;
boolean read_interruttori = false;

int in_croce = A2;
boolean sign_croce = true;
boolean read_croce = false;

int in_start = A4;
boolean sign_start = true;
boolean read_start = false;

int in_foto = A5;
boolean sign_foto = true;
boolean read_foto = false;

int in_stereo = A6;
boolean sign_stereo = true;
boolean read_stereo = false;

int in_culla = A7;
boolean sign_culla = true;
boolean read_culla = false;

int in_orologi = A8;
boolean sign_orologi = true;
boolean read_orologi = false;

int in_organo = A9;
boolean sign_organo = true;
boolean read_organo = false;

int in_libero = A10;
boolean sign_libero = true;
boolean read_libero = false;

int in_timone = A11;
boolean sign_timone = true;
boolean read_timone = false;

// output variabili
int valvole = 22;
int danger = 23;
int mano = 24;
int motore = 25;
int croce = 26;
int monaco = 27;
int timone = 28;
int candele = 29;
int culla = 30;
int culla_start = 31;
int foto = 32;
int stereo = 33;
int timone_segnale = 34;
int ventilatore = 35;
int orologi = 36;
int organo = 37;
int pulsanti = 38;
int organo_start = 39;
int nano = 40;
// 220 volts
int luce_gen = 41;
int luce_gran = 42;
// elettrocalamite
int M1 = 43;
int M2 = 44;
int M3 = 45;
int M4 = 46;
int M5 = 47;
int M6 = 48;
int M7 = 49;
int M8 = 50;
int M9 = 51;
int M10 = 52;
int libero = 53;

void setup()
 {
   // OUTPUT
   for (int i = 29; i < 54; i++){
     pinMode(i,OUTPUT);
   }
   for (int i = 2; i < 6; i++){
     pinMode(i,OUTPUT);
   }
    pinMode(led, OUTPUT); // Set pin 13 as digital out

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
    myDFPlayer.volume (20);
    Serial.println("You are Welcome!");
}

void loop()
{
  if (stringComplete) {
    //Serial.println(input);
    seriale();
    input = "";
    stringComplete = false;
  }
  
//game();
//lettura();

}

void game () {

  if (start_game){
    // chiudi tutte le elettrocalamite
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
    digitalWrite(M3, HIGH);
    digitalWrite(M4, HIGH);
    digitalWrite(M5, HIGH);
    digitalWrite(M6, HIGH);
    digitalWrite(M7, HIGH);
    digitalWrite(M8, HIGH);
    digitalWrite(M9, HIGH);
    digitalWrite(M10, HIGH);
    // accendi
    digitalWrite(candele, HIGH);
    digitalWrite(valvole, HIGH);
    digitalWrite(danger, HIGH);
    digitalWrite(luce_gen, HIGH);
    digitalWrite(luce_gran, HIGH);
    start_game = false;
  }
  sign_valvole = digitalRead(in_valvole);
  if (!sign_valvole){
    digitalWrite(danger, LOW); // switch off "DANGER"
    digitalWrite(motore, HIGH); // switch on motor
    digitalWrite(M1, LOW); // open the door
  }

  sign_motore = digitalRead(in_motore);
  if (!sign_motore){
    digitalWrite(M2, LOW); // open the door
  }

  // if the players are on the second floor
  if (second_floor){
    digitalWrite(ventilatore, HIGH);
    delay(5000);
    digitalWrite(candele, LOW);
    digitalWrite(ventilatore,LOW);
    digitalWrite(stereo, HIGH);
    digitalWrite(culla, HIGH);
    second_floor = false;
  }

  sign_start = digitalRead(in_start);
  if (!read_start && !sign_start){
    start_game = true;
    read_start = true;
    sign_start = true;
  }
}

void lettura() {
  sign_valvole = digitalRead(in_valvole);
  if (!read_valvole && !sign_valvole){
    Serial.println("valvole");
    read_valvole = true;
  }
  sign_motore = digitalRead(in_motore);
  if (!read_motore && !sign_motore){
    Serial.println("motore");
    read_motore = true;
  }

}

void serialEvent() {
  
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
  void seriale() {
    //Serial.print("Seriale inizio: ");
    //Serial.println(input);
  if (input == "A"){
    digitalWrite(valvole,HIGH);
    Serial.println("Valve ON");
  }
  if (input == "a"){
    digitalWrite(valvole,LOW);
    Serial.println("Valve OFF");
  }

  if (input == 'B'){
    digitalWrite(danger,HIGH);
  }
  if (input == 'b'){
    digitalWrite(danger,LOW);
  }

  if (input == 'C'){
    digitalWrite(danger, HIGH);
  }
  if (input == 'c'){
    digitalWrite(danger,LOW);
  }

  if (input == 'D'){
    digitalWrite(motore, HIGH);
  }
  if (input == 'd'){
    digitalWrite(motore, LOW);
  }

  if (input == 'E'){
    digitalWrite(croce, HIGH);
  }
  if (input == 'e'){
    digitalWrite(croce, LOW);
  }

  if (input == 'F'){
    digitalWrite(monaco, HIGH);
  }
  if (input == 'f'){
    digitalWrite(monaco, LOW);
  }

  if (input == 'G'){
    digitalWrite(timone, HIGH);
  }
  if (input == 'g'){
    digitalWrite(timone, LOW);
  }

  if (input == 'H'){
    digitalWrite(candele, HIGH);
  }
  if (input == 'h'){
    digitalWrite(candele, LOW);
  }

  if (input == 'I'){
    digitalWrite(culla, HIGH);
  }
  if (input == 'i'){
    digitalWrite(culla, LOW);
  }

  if (input == 'J'){
    digitalWrite(culla_start, HIGH);
  }
  if (input == 'j'){
    digitalWrite(culla_start, LOW);
  }

  if (input == 'K'){
    digitalWrite(foto, HIGH);
  }
  if (input == 'k'){
    digitalWrite(foto, LOW);
  }

  if (input == 'L'){
    digitalWrite(stereo, HIGH);
  }
  if (input == 'l'){
    digitalWrite(stereo, LOW);
  }

  if (input == 'M'){
    digitalWrite(ventilatore, HIGH);
  }
  if (input == 'm'){
    digitalWrite(ventilatore, LOW);
  }

  if (input == 'O'){
    digitalWrite(orologi, HIGH);
  }
  if (input == 'o'){
    digitalWrite(orologi, LOW);
  }

  if (input == 'P'){
    digitalWrite(organo, HIGH);
  }
  if (input == 'p'){
    digitalWrite(organo, LOW);
  }

  if (input == 'Q'){
    digitalWrite(pulsanti, HIGH);
  }
  if (input == 'q'){
    digitalWrite(pulsanti, LOW);
  }

  if (input == 'R'){
    digitalWrite(nano, HIGH);
  }
  if (input == 'r'){
    digitalWrite(nano, LOW);
  }

  if (input == 'S'){
    digitalWrite(organo_start, HIGH);
  }
  if (input == 's'){
    digitalWrite(organo_start, LOW);
  }

  if (input == 'Y'){
    digitalWrite(luce_gen, HIGH);
  }
  if (input == 'y'){
    digitalWrite(luce_gen, LOW);
  }

  if (input == 'Z'){
    digitalWrite(luce_gran, HIGH);
  }
  if (input == 'z'){
    digitalWrite(luce_gran, LOW);
  }

  // electromagnets
  if (input == '!') {
    digitalWrite(M1, HIGH);
  }
  if (input == '1') {
    digitalWrite(M1, LOW);
  }

  if (input == '@') {
    digitalWrite(M2, HIGH);
  }
  if (input == '2') {
    digitalWrite(M2, LOW);
  }

  if (input == '#') {
    digitalWrite(M3, HIGH);
  }
  if (input == '3') {
    digitalWrite(M3, LOW);
  }

  if (input == '$') {
    digitalWrite(M4, HIGH);
  }
  if (input == '4') {
    digitalWrite(M4, LOW);
  }

  if (input == '%') {
    digitalWrite(M5, HIGH);
  }
  if (input == '5') {
    digitalWrite(M5, LOW);
  }

  if (input == '^') {
    digitalWrite(M6, HIGH);
  }
  if (input == '6') {
    digitalWrite(M6, LOW);
  }

  if (input == '&') {
    digitalWrite(M7, HIGH);
  }
  if (input == '7') {
    digitalWrite(M7, LOW);
  }

  if (input == '*') {
    digitalWrite(M8, HIGH);
  }
  if (input == '8') {
    digitalWrite(M8, LOW);
  }

  if (input == '(') {
    digitalWrite(M9, HIGH);
  }
  if (input == '9') {
    digitalWrite(M9, LOW);
  }

  if (input == ')') {
    digitalWrite(M10, HIGH);
  }
  if (input == '0'){
    digitalWrite(M10, LOW);
  }

  // animations
  if (input == 'N')
  {
    digitalWrite(ventilatore, HIGH);
    delay(5000);
    digitalWrite(candele, LOW);
    delay(200);
    digitalWrite(ventilatore, LOW);
  }

  // start
  if (input == 'start_game'){
      start_game = true;
  }

  // test serial
  if (input == 'test_on')
  {
      digitalWrite(led, HIGH);
  }
  else if (input == 'test_off')
  {
      digitalWrite(led, LOW);
  }

    Serial.print("Seriale fine: ");
    Serial.println(input);
}
