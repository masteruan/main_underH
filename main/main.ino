/*
 Main sottoterra
 2 Giugno 2017

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
SoftwareSerial mySoftwareSerial(6, 7); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// Variables
int lang;
int led = 13; // Pin 13

// switch
boolean start_game = false;
boolean game_started = false;
boolean second_floor = false;
boolean preparation = false;
boolean scatolaGrande = false;
boolean OK_secondFloor = false;

// serial
boolean stringComplete = false;
String input = ""; //String
char inChar ;

// input Variables
int games[] = {A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11};

int in_valvole = A0;
boolean sign_valvole = true;
boolean read_valvole = false;
boolean OK_valvole = false;

int in_generatore = A10;
boolean sign_generatore = false;
boolean read_generatore = false;
boolean OK_generatore = false;

int in_motore = A1;
boolean sign_motore = true;
boolean read_motore = false;
boolean OK_motore = false;

int in_interruttori = A3;
boolean sign_interruttori = true;
boolean read_interruttori = false;
boolean OK_interruttori = false;

int in_croce = A2;
boolean sign_croce = true;
boolean read_croce = false;
boolean OK_croce = false;

int in_start = A4;
boolean sign_start = true;
boolean read_start = false;
boolean OK_start = false;

int in_foto = A5;
boolean sign_foto = true;
boolean read_foto = false;
boolean OK_foto = false;

int in_stereo = A6;
boolean sign_stereo = true;
boolean read_stereo = false;
boolean OK_stereo = false;

int in_culla = A7;
boolean sign_culla = true;
boolean read_culla = false;
boolean OK_culla = false;

int in_orologi = A8;
boolean sign_orologi = true;
boolean read_orologi = false;
boolean OK_orologi = false;

int in_organo = A9;
boolean sign_organo = true;
boolean read_organo = false;
boolean OK_organo = false;

int in_libero = A10;
boolean sign_libero = true;
boolean read_libero = false;
boolean OK_libero = false;

int in_timone = A11;
boolean sign_timone = true;
boolean read_timone = false;
boolean OK_timone = false;

// output variabili
int valvole = 22;
int danger = 23;
int mano = 24;
int motore = 25;
int croce = 35; //default 26
int monaco = 27;
int timone = 28;
int candele = 29;
int culla = 30;
int culla_start = 31;
int foto = 32;
int stereo = 33;

//int timone_segnale = 34;
int ventilatore = 34;

int orologi = 36;
int organo = 37;
int pulsanti = 41;
int nano = 39;
int organo_start = 40;
int libero1 = 41;
int libero2 = 42;
// luci 220 volts
int luce_primo = 9;
int luce_secondo = 10;
int luce_terzo = 11;
int luce_quarto = 12;
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
int M11 = 53;



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
    //Serial.println(input);
    seriale();
    input = "";
    stringComplete = false;
  }
game();
//lettura();

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
    digitalWrite(M11, HIGH);
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
    OK_valvole = true;
  }
  delay(10);
  if(OK_valvole){
    sign_generatore = digitalRead(in_generatore);
  }
  if (sign_generatore && !OK_generatore){
    digitalWrite(luce_quarto, HIGH);
    digitalWrite(luce_terzo, HIGH);
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
    OK_motore = true;
  }

  // if the players are on the second floor
  if (second_floor && !OK_secondFloor){
    digitalWrite(M11, HIGH); //cella croce
    delay(200);
    digitalWrite(monaco, LOW);
    digitalWrite(luce_primo, HIGH);
    digitalWrite(candele, HIGH);   
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
    OK_culla = true;
  }
  if(OK_culla){
    sign_timone = digitalRead(in_timone);
  }
  if (!sign_timone && !OK_timone) {
    digitalWrite(M9, LOW); //sblocca la porta per gli orologi
    OK_timone = true;
    digitalWrite(orologi, HIGH);
  }
  if(OK_timone){
    sign_orologi = digitalRead(in_orologi);
  }
  if (!sign_orologi && !OK_orologi) {
    digitalWrite(M5, LOW);// apre porta per il nano
    digitalWrite(luce_primo, HIGH);
    delay(6000);
    digitalWrite(nano, HIGH);
    delay(100);
    digitalWrite(organo, HIGH);
    delay(200);
    digitalWrite(organo, LOW);
    delay(200);
    digitalWrite(organo,HIGH);
    digitalWrite(pulsanti, HIGH);
    OK_orologi = true;
  }
  //if(OK_orologi){
    sign_organo = digitalRead(in_interruttori);
  //}
  if (!sign_organo && !OK_organo) {
    digitalWrite(nano,LOW);
    digitalWrite(luce_primo,LOW);
    digitalWrite(luce_secondo, HIGH); // accendi la luce finale
    delay(10000);
    digitalWrite(mano, HIGH);
    OK_organo = true;
  }
  if(OK_organo){
    //reset all
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

void lettura() {
  sign_valvole = digitalRead(in_valvole);
  delay(10);
  sign_generatore = !digitalRead(in_generatore);
  delay(10);
  sign_motore = digitalRead(in_motore);
  delay(10);
  sign_organo = digitalRead(in_organo);
  delay(10);
  sign_orologi = digitalRead(in_orologi);
  delay(10);
  sign_foto = digitalRead(in_foto);
  delay(10);
  sign_timone = digitalRead(in_timone);
  delay(10);
  sign_croce = digitalRead(in_croce);
  delay(10);
  sign_culla = digitalRead(in_culla);
  delay(10);
  sign_stereo = digitalRead(in_stereo);
  delay(10);
  sign_interruttori = digitalRead(in_interruttori);

  if (!sign_valvole){
    Serial.println("valvole risolte");
  }
  if (!sign_generatore){
    Serial.println("generatore risolto");
  }
  if (!sign_motore){
    Serial.println("motore risolte");
  }
  if (!sign_interruttori){
    Serial.println("interruttori risolti");
  }
  if (!sign_stereo){
    Serial.println("stereo risolte");
  }
  if(!sign_culla){
    Serial.println("culla risolta");
  }
  if(!sign_croce){
    Serial.println("croce risolta");
  }
  if(!sign_foto){
    Serial.println("foto risolta");
  }
  if(!sign_timone){
    Serial.println("timone risolto");
  }
  if(!sign_orologi){
    Serial.println("orologi risolti");
  }
  if(!sign_organo){
    Serial.println("organo risolto");
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
  void seriale() {
  if (input[0] == 'A'){
    digitalWrite(valvole, HIGH);
  }

  else if (input[0] == 'a'){
    digitalWrite(valvole, LOW);
  }

  else if (input[0] == 'B'){
    digitalWrite(danger,HIGH);
  }

  else if (input[0] == 'b'){
    digitalWrite(danger,LOW);
  }

  else if (input[0] == 'C'){
    digitalWrite(danger, HIGH);
  }

  else if (input[0] == 'c'){
    digitalWrite(danger,LOW);
  }

  else if (input[0] == 'D'){
    digitalWrite(motore, HIGH);
  }

  else if (input[0] == 'd'){
    digitalWrite(motore, LOW);
  }

  else if (input[0] == 'E'){
    digitalWrite(croce, HIGH);
  }

  else if (input[0] == 'e'){
    digitalWrite(croce, LOW);
  }

  else if (input[0] == 'F'){
    digitalWrite(monaco, HIGH);
  }

  else if (input[0] == 'f'){
    digitalWrite(monaco, LOW);
  }

  else if (input[0] == 'G'){
    digitalWrite(timone, HIGH);
  }

  else if (input[0] == 'g'){
    digitalWrite(timone, LOW);
  }

  else if (input[0] == 'H'){
    digitalWrite(candele, HIGH);
  }

  else if (input[0] == 'h'){
    digitalWrite(candele, LOW);
  }

  else if (input[0] == 'I'){
    digitalWrite(culla, HIGH);
  }

  else if (input[0] == 'i'){
    digitalWrite(culla, LOW);
  }

  else if (input[0] == 'J'){
    digitalWrite(culla_start, HIGH);
  }

  else if (input[0] == 'j'){
    digitalWrite(culla_start, LOW);
  }

  else if (input[0] == 'K'){
    digitalWrite(foto, HIGH);
  }

  else if (input[0] == 'k'){
    digitalWrite(foto, LOW);
  }

  else if (input[0] == 'L'){
    digitalWrite(stereo, HIGH);
  }

  else if (input[0] == 'l'){
    digitalWrite(stereo, LOW);
  }

  else if (input[0] == 'M'){
    digitalWrite(ventilatore, HIGH);
  }

  else if (input[0] == 'm'){
    digitalWrite(ventilatore, LOW);
  }

  else if (input[0] == 'O'){
    digitalWrite(orologi, HIGH);
  }

  else if (input[0] == 'o'){
    digitalWrite(orologi, LOW);
  }

  else if (input[0] == 'P'){
    digitalWrite(organo, HIGH);
  }

  else if (input[0] == 'p'){
    digitalWrite(organo, LOW);
  }

  else if (input[0] == 'Q'){
    digitalWrite(pulsanti, HIGH);
  }

  else if (input[0] == 'q'){
    digitalWrite(pulsanti, LOW);
  }

  else if (input[0] == 'R'){
    digitalWrite(nano, HIGH);
  }

  else if (input[0] == 'r'){
    digitalWrite(nano, LOW);
  }

  else if (input[0] == 'S'){
    digitalWrite(organo_start, HIGH);
  }

  else if (input[0] == 's'){
    digitalWrite(organo_start, LOW);
  }

  else if (input[0] == 'Y'){
    digitalWrite(libero1, HIGH);
  }

  else if (input[0] == 'y'){
    digitalWrite(libero1, LOW);
  }

  else if (input[0] == 'Z'){
    digitalWrite(libero2, HIGH);
  }

  else if (input[0] == 'z'){
    digitalWrite(libero2, LOW);
  }

  // luci
  else if (input == "#A\n"){
    digitalWrite(luce_primo, HIGH);
  }
  else if (input == "#a\n"){
    digitalWrite(luce_primo, LOW);
  }
  else if (input == "#B\n"){
    digitalWrite(luce_secondo, HIGH);
  }
  else if (input == "#b\n"){
    digitalWrite(luce_secondo, LOW);
  }
  else if (input == "#C\n"){
    digitalWrite(luce_terzo, HIGH);
  }
  else if (input == "#c\n"){
    digitalWrite(luce_terzo, LOW);
  }
  else if (input == "#D\n"){
    digitalWrite(luce_quarto, HIGH);
  }
  else if (input == "#d\n"){
    digitalWrite(luce_quarto, LOW);
  }
  // electromagnets
  else if (input[0] == '!') {
    digitalWrite(M1, HIGH);
  }
  else if (input[0] == '1') {
    digitalWrite(M1, LOW);
  }

  else if (input[0] == '@') {
    digitalWrite(M2, HIGH);
  }
  else if (input[0] == '2') {
    digitalWrite(M2, LOW);
  }

  else if (input[0] == '£') {
    digitalWrite(M3, HIGH);
  }
  else if (input[0] == '3') {
    digitalWrite(M3, LOW);
  }

  else if (input[0] == '$') {
    digitalWrite(M4, HIGH);
  }
  else if (input[0] == '4') {
    digitalWrite(M4, LOW);
  }

  else if (input[0] == '%') {
    digitalWrite(M5, HIGH);
  }
  else if (input[0] == '5') {
    digitalWrite(M5, LOW);
  }

  else if (input[0] == '^') {
    digitalWrite(M6, HIGH);
  }
  else if (input[0] == '6') {
    digitalWrite(M6, LOW);
  }

  else if (input[0] == '&') {
    digitalWrite(M7, HIGH);
  }
  else if (input[0] == '7') {
    digitalWrite(M7, LOW);
  }

  else if (input[0] == '*') {
    digitalWrite(M8, HIGH);
  }
  else if (input[0] == '8') {
    digitalWrite(M8, LOW);
  }

  else if (input[0] == '(') {
    digitalWrite(M9, HIGH);
  }
  else if (input[0] == '9') {
    digitalWrite(M9, LOW);
  }

  else if (input[0] == ')') {
    digitalWrite(M10, HIGH);
  }
  else if (input[0] == '0'){
    digitalWrite(M10, LOW);
  }
  else if (input[0] == 'N'){
    digitalWrite(M11, HIGH);
  }
  else if (input[0] == 'n'){
    digitalWrite(M11, LOW);
  }
  // animations
  else if (input == "_vent\n")
  {
    digitalWrite(ventilatore, HIGH);
    delay(5000);
    digitalWrite(candele, LOW);
    delay(200);
    digitalWrite(ventilatore, LOW);
  }
  else if (input == "_nano\n"){
      digitalWrite(nano, LOW);
      delay(200);
      digitalWrite(nano, HIGH);
  }

  // start
  else if (input == "_startGame\n" && !start_game){
      start_game = true;
      game_started = false;
      Serial.println("Start Game");
  }

  // second floor
  else if (input == "_secondFloor\n" && !second_floor){
    second_floor = true;
    Serial.println("Gamers on second floors!");
  }
  // scatola grande
  else if (input == "_scatolaGrande\n" && !scatolaGrande){
    scatolaGrande = true;
    digitalWrite(M8, LOW);
    //Serial.println("The big box opened!");
  }
  // preparation
  //(remember the big box that have the "scrocco" not electromagnets)
  else if (input == "_preparation\n" && !preparation){
    preparation = true;
    Serial.println("Go to close all the doors!");
    // close all the doors
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
    digitalWrite(M3, HIGH);
    digitalWrite(M4, HIGH);
    digitalWrite(M5, HIGH);
    digitalWrite(M6, HIGH);
    digitalWrite(M7, LOW); // scatola piccola
    digitalWrite(M8, HIGH);
    digitalWrite(M9, HIGH);
    digitalWrite(M10, HIGH);
    digitalWrite(monaco, HIGH);
    digitalWrite(timone, HIGH);
    // switch on all the lights
    digitalWrite(luce_primo, HIGH);
    delay(200);
    digitalWrite(luce_secondo, HIGH);
    delay(200);
    digitalWrite(luce_terzo, HIGH);
    delay(200);
    digitalWrite(luce_quarto, HIGH);

  }
  // open all
  else if (input == "_openAll\n"){
    // open all the doors
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
    digitalWrite(M3, LOW);
    digitalWrite(M4, LOW);
    digitalWrite(M5, LOW);
    digitalWrite(M6, LOW);
    digitalWrite(M7, HIGH);
    delay(100);
    digitalWrite(M7, LOW);
    digitalWrite(M8, LOW);
    digitalWrite(M9, LOW);
    digitalWrite(M10, LOW);
    digitalWrite(M11, LOW);
    // switch on all the lights
    digitalWrite(luce_primo, HIGH);
    delay(200);
    digitalWrite(luce_secondo, HIGH);
    delay(200);
    digitalWrite(luce_terzo, HIGH);
    delay(200);
    digitalWrite(luce_quarto, HIGH);
  }
  // Test all pins ON
  /*else if (input == "_allON\n");
    for (int i = 22; i < 54; i++){
      digitalWrite(i, HIGH);
      Serial.print("Accensione pin: ");
      Serial.println(i);
      delay(1000);
    }
    */
  // lettura giochi
  else if (input == "_lettura\n"){
    Serial.println("\nLettura input");
    lettura();
  }

  // test serial
  else if (input == "_test_on\n")
  {
      for (int i = 0; i < 10; i++) {
        digitalWrite(led, HIGH);
        delay(100);
        digitalWrite(led, LOW);
      }
  }
}
