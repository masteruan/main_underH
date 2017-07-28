/*
 Main sottoterra
 28 Luglio 2017
 v 3.4
 Now the gamemaster can resolves the game. (HV,HG...)

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
Organo 37         --  Pulsanti  41
Orologi 36        --  Organo play 39
Ventilatore 35    --  Nano 40
Timone (segle) 34 --  Libero --
Stereo 33         --  Libero 42
Foto 32           --  M1 43
ex culla gira31   --  M2 44
Culla 30          --  Culla (gira) 6
--                --
RELAY PICCOLI
audio
ralay1 4  --  relay3 3
relay2 5  --  relay4 2
RELAY 220 V

LUCI
luce_terzo 11(Sala Grande, croce)|luce_quarto 12(Ingresso,orologi,scala,Interruttori)
luce_secondo 10(Uscita)|luce_primo 9(nano,bambini,Organo)

INPUT
Timone A11  --  Libero A10
Organo A9   --  Orologi A8
Culla A7    --  Stereo A6
Foto A5     --  Start A4
Croce A2    --  Interruttori A3
Motore A1   --  Valvole A0

DOORS
M1 per Motore
M2 per sala grande
M4 dopo scala
M5 per Organo
M6 per scala secondo piano
M7 scatola piccola (scrocco)
M8 scatola Grande
M9 per orologi
M10 per timone
M11 cella della croce

Instructions
Send to serial
"_preparation" to close all the doors and switch on all the lights
"_startGame" to start the game
"_secondFloor" to switch on the second floor
"_vent" for the animation of ventilator
"_nano" for the animation of dwarf
"_special1" for audio special in cross (mouses)
"_special2" for audio special in timone (baby)
"_special3" for audio special in timone (baby2)

Game resolution
HV Valvole
HG generatore
HM motore
HC croce
HF foto
HS stereo
HU culla
HT timone
HO orologi
HR organo
*/

// Libraries
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
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
boolean OK_valvole = false;

int in_generatore = A10;
boolean sign_generatore = false;
boolean OK_generatore = false;

int in_motore = A1;
boolean sign_motore = true;
boolean OK_motore = false;

int in_interruttori = A3;
boolean sign_interruttori = true;
boolean OK_interruttori = false;

int in_croce = A2;
boolean sign_croce = true;
boolean OK_croce = false;

int in_start = A4;
boolean sign_start = true;
boolean OK_start = false;

int in_foto = A5;
boolean sign_foto = true;
boolean OK_foto = false;

int in_stereo = A6;
boolean sign_stereo = true;
boolean OK_stereo = false;

int in_culla = A7;
boolean sign_culla = true;
boolean OK_culla = false;

int in_orologi = A8;
boolean sign_orologi = true;
boolean OK_orologi = false;

int in_organo = A9;
boolean sign_organo = true;
boolean OK_organo = false;

int in_libero = A10;
boolean sign_libero = true;
boolean OK_libero = false;

int in_timone = A11;
boolean sign_timone = true;
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
int culla_gira = 6;

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

typedef struct {
  String str;
  int pin;
} output;
output outputs[35]={
  {"valvole", valvole},
  {"danger", danger},
  {"mano", mano},
  {"motore", motore},
  {"croce", croce}, //default 26
  {"monaco", monaco},
  {"timone", timone},
  {"candele", candele},
  {"culla", culla},
  {"culla_gira", culla_gira},
  {"foto", foto},
  {"stereo", stereo},
  //{"timone_segnale", 34},
  {"ventilatore", ventilatore},
  {"orologi", orologi},
  {"organo", organo},
  {"pulsanti", pulsanti},
  {"nano", nano},
  {"organo_start", organo_start},
  {"libero1", libero1},
  {"libero2", libero2},
  // luci 220 volts
  {"luce_primo", luce_primo},
  {"luce_secondo", luce_secondo},
  {"luce_terzo", luce_terzo},
  {"luce_quarto", luce_quarto},
  // elettrocalamite
  {"M1", M1},
  {"M2", M2},
  {"M3", M3},
  {"M4", M4},
  {"M5", M5},
  {"M6", M6},
  {"M7", M7},
  {"M8", M8},
  {"M9", M9},
  {"M10", M10},
  {"M11", M11}
};

boolean H_valvole = false ;
boolean H_generatore = false ;
boolean H_motore = false ;
boolean H_croce = false ;
boolean H_foto = false ;
boolean H_stereo = false ;
boolean H_culla = false ;
boolean H_orologi = false ;
boolean H_organo = false ;
boolean H_timone =false ;


void setup() {
  Serial.flush();
  // OUTPUT
  for (int i = 22; i < 54; i++){
    pinMode(i,OUTPUT);
  }
  for (int i = 2; i < 7; i++){
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
    Serial1.begin(9600); //default 9600
    Serial.begin(9600); //default 115200
    input.reserve(200);

    // Start mp3 player
    if (!myDFPlayer.begin(Serial1)) {  //Use softwareSerial to communicate with mp3.
      Serial.println(F("Unable to begin:"));
      Serial.println(F("1.Please recheck the connection!"));
      Serial.println(F("2.Please insert the SD card!"));
      //while(true);
    }
    /* Debug Audio Special
    Serial.println("Play special sound");
    myDFPlayer.volume(30); // min = 0 max = 30
    for (int i = 0; i < 9; i++) {
      Serial.print("Play no. ");
      Serial.println(i);
      myDFPlayer.play(i);
      delay(5000);
    }
    Serial.println("change special sound");
    digitalWrite(4, 1);
    digitalWrite(5, 1);
    myDFPlayer.play(2);
    delay(5000);
    digitalWrite(4, 0);
    digitalWrite(5, 0);
    */

    Serial.println("################");
    Serial.println("You are Welcome!");
}

void loop() {
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
    OK_valvole = false;
    OK_motore = false;
    OK_generatore = false;
    OK_interruttori = false;
    OK_secondFloor = false;
    OK_croce = false;
    OK_foto = false;
    OK_stereo = false;
    OK_culla = false;
    OK_orologi = false;
    OK_organo = false;
    OK_timone = false;

    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
    digitalWrite(M3, HIGH);
    delay(50);
    digitalWrite(M4, HIGH);
    digitalWrite(M5, HIGH);
    digitalWrite(M6, HIGH);
    delay(50);
    digitalWrite(M8, HIGH);
    digitalWrite(M9, HIGH);
    digitalWrite(M10, HIGH);
    delay(50);
    digitalWrite(M11, HIGH);
    digitalWrite(croce, HIGH);
    digitalWrite(culla_gira, HIGH);
    // spegni luci
    digitalWrite(luce_primo, LOW);
    delay(50);
    digitalWrite(luce_secondo, LOW);
    delay(50);
    digitalWrite(luce_terzo, LOW);
    delay(50);
    digitalWrite(luce_quarto, LOW);
    delay(50);
    digitalWrite(valvole, HIGH);
    start_game = false;
    game_started = true;
    Serial.println("gameStarted");
  }
  else if (game_started){

    if (!OK_valvole){
      sign_valvole = digitalRead(in_valvole);
      }
    if ((!sign_valvole || H_valvole) && !OK_valvole){
      for(int i=0; i<5; i++) {Serial.println("valvoleDone");}
      digitalWrite(danger, HIGH); // switch off "DANGER"
      digitalWrite(motore, HIGH); // switch on motor
      digitalWrite(M1, LOW); // open the door
      OK_valvole = true;
    }
    delay(10);
    if(OK_valvole){
      sign_generatore = digitalRead(in_generatore);
      digitalWrite(valvole,LOW);
    }
    if ((sign_generatore || H_generatore) && !OK_generatore){
      for(int i=0; i <5 ;i++ ) {Serial.println("generatoreDone");}
      digitalWrite(luce_quarto, HIGH);
      OK_generatore = true;
    }
    if(OK_generatore){
      sign_motore = digitalRead(in_motore);
    }
    if ((!sign_motore || H_motore) && !OK_motore){
      for(int i=0; i <5 ;i++ ) {Serial.println("motoreDone");}
      digitalWrite(M2, LOW); // open the door
      digitalWrite(M11, LOW);
      delay(2000);
      digitalWrite(monaco, HIGH);
      OK_motore = true;
    }

    // if the players are on the second floor
    if (second_floor && !OK_secondFloor){
      digitalWrite(M11, HIGH); //cella croce
      delay(200);
      digitalWrite(monaco, LOW);
      digitalWrite(candele, HIGH);
      OK_secondFloor = true;
    }

    // waiting for operator "_vent" & off tutti i caschi
    // waiting for operator unlock the BIG BOX (JAVA) _scatolaGrande
    if (OK_secondFloor){
      sign_croce = digitalRead(in_croce);
    }
    if ((!sign_croce || H_croce) && !OK_croce){
      for(int i=0; i <5 ;i++ ){Serial.println("croceDone");}
      digitalWrite(M7, HIGH); //sblocca scatola piccola
      delay(20);
      digitalWrite(M11, LOW); //cella della croce
      delay(20);
      digitalWrite(foto, HIGH);
      delay(50);
      digitalWrite(luce_quarto, LOW);
      delay(50);
      digitalWrite(luce_terzo, HIGH);
      OK_croce = true;
    }
    if(OK_croce) {
      sign_foto = digitalRead(in_foto);
    }
    if ((!sign_foto || H_foto) && !OK_foto){
      for(int i=0; i <5 ;i++ ){Serial.println("fotoDone");}
      digitalWrite(luce_primo, HIGH);
      delay(50);
      digitalWrite(stereo, HIGH);
      delay(3000);
      digitalWrite(culla, HIGH); // accende la culla
      delay(20);
      OK_foto = true;
    }
    if(OK_foto) {
      sign_stereo = digitalRead(in_stereo);
    }
    if ((!sign_stereo || H_stereo) && !OK_stereo){
      for(int i=0; i <5 ;i++ ){Serial.println("stereoDone");}
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
    if ((!sign_culla || H_culla) && !OK_culla){
      for(int i=0; i <5 ;i++ ){Serial.println("cullaDone");}
      digitalWrite(M10, LOW); // sblocca cella timone
      delay(50);
      // special sound timone
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      myDFPlayer.volume(30); // min = 0 max = 30
      myDFPlayer.play(3);
      delay(100);
      digitalWrite(timone, HIGH);
      delay(50);
      digitalWrite(M7, LOW); //rilascia la calamita scatola piccola
      delay(3000);
      myDFPlayer.play(3);
      digitalWrite(luce_primo, LOW);
      OK_culla = true;
    }
    if(OK_culla){
      sign_timone = digitalRead(in_timone);
      digitalWrite(culla, LOW);
    }
    if ((!sign_timone || H_timone) && !OK_timone) {
      for(int i=0; i <5 ;i++ ){Serial.println("timoneDone");}
    digitalWrite(M9, LOW); //sblocca la porta per gli orologi
    digitalWrite(orologi, HIGH);
    digitalWrite(luce_quarto, HIGH);
    OK_timone = true;
    }
    delay(1000);
    if(OK_timone){
    sign_orologi = digitalRead(in_orologi);
    }
    if ((!sign_orologi || H_orologi) && !OK_orologi) {
      for(int i=0; i <5 ;i++ ){Serial.println("orologiDone");}
      digitalWrite(M5, LOW);// apre porta per il nano
      digitalWrite(luce_quarto, LOW);
      delay(6000);
      digitalWrite(luce_primo, HIGH);
      digitalWrite(nano, HIGH);
      delay(100);
      digitalWrite(organo, HIGH);
      delay(200);
      digitalWrite(pulsanti, HIGH);
      OK_orologi = true;
    }
    if(OK_orologi){
      sign_organo = digitalRead(in_interruttori);
    }
    if ((!sign_organo || H_organo) && !OK_organo) {
      for(int i=0; i <5 ;i++ ){Serial.println("organoDone");}
      digitalWrite(nano,LOW);
      delay(50);
      digitalWrite(luce_primo, LOW);
      digitalWrite(luce_secondo, HIGH); // accendi la luce finale
      delay(10000);
      digitalWrite(mano, HIGH);
      OK_organo = true;
    }
    if(OK_organo){
    Serial.println("THE END");
    }
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
  delay(100);
  if (!sign_generatore){
    Serial.println("generatore risolto");
  }
  delay(100);
  if (!sign_motore){
    Serial.println("motore risolte");
  }
  delay(100);
  if (!sign_interruttori){
    Serial.println("interruttori risolti");
  }
  delay(100);
  if (!sign_stereo){
    Serial.println("stereo risolte");
  }
  delay(100);
  if(!sign_culla){
    Serial.println("culla risolta");
  }
  delay(100);
  if(!sign_croce){
    Serial.println("croce risolta");
  }
  delay(100);
  if(!sign_foto){
    Serial.println("foto risolta");
  }
  delay(100);
  if(!sign_timone){
    Serial.println("timone risolto");
  }
  delay(100);
  if(!sign_orologi){
    Serial.println("orologi risolti");
  }
  delay(100);
  if(!sign_organo){
    Serial.println("organo risolto");
  }
  delay(100);

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
  int index = input.indexOf(',');
  int pin;
  if(index != -1){
    for (int k=0; k<35; k++){
      if (input.substring(0,index) == outputs[k].str){
        pin = outputs[k].pin;
      }
    }
    int state = (input.substring(index+1,index+2)).toInt();
    digitalWrite(pin,state);
}

  else if (input == "HV\n")
  {
    H_valvole = true;
  }
  else if (input == "HG\n")
  {
   H_generatore = true;
  }
  else if (input == "HM\n")
  {
    H_motore=true;
  }
  else if (input == "HC\n")
  {
   H_croce=true;
  }
  else if (input == "HF\n")
  {
    H_foto=true;
  }
  else if (input == "HS\n")
  {
   H_stereo=true;
  }
  else if (input == "HU\n")
  {
    H_culla=true;
  }
  else if (input == "HO\n")
  {
    H_orologi=true;
  }
  else if (input == "HT\n")
  {
    H_timone=true;
  }
  else if (input == "HR\n")
  {
    H_organo=true;
  }
  // animations
  else if (input == "_vent\n")
  {
  digitalWrite(ventilatore, HIGH);
  delay(5000);
  digitalWrite(candele, LOW);
  delay(200);
  digitalWrite(ventilatore, LOW);
  digitalWrite(luce_primo, HIGH);
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
  // Special Audio cross
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  myDFPlayer.volume(20); // min = 0 max = 30
  myDFPlayer.play(7);
  delay(50);
  }
  // preparation
  //(remember the big box that have the "scrocco" not electromagnets)
  else if (input == "_preparation\n" && !preparation){
  preparation = true;
  Serial.println("Go to close all the doors!");
  digitalWrite(organo,HIGH);
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
  digitalWrite(culla_gira, HIGH);
  // switch on all the lights
  digitalWrite(luce_primo, HIGH);
  delay(200);
  digitalWrite(luce_secondo, HIGH);
  delay(200);
  digitalWrite(luce_terzo, HIGH);
  delay(200);
  digitalWrite(luce_quarto, HIGH);
  delay(200);
  digitalWrite(organo_start,HIGH);
  delay(2000);
  digitalWrite(organo_start,LOW);

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

  // lettura giochi
  else if (input == "_lettura\n"){
  Serial.println("\nLettura input");
  lettura();
  }

  // special sound
  else if (input == "_special1\n"){
    // change on cross audio
    digitalWrite(4, 0);
    digitalWrite(5, 0);
    myDFPlayer.volume(30); // min = 0 max = 30
    myDFPlayer.play(8);
    delay(5000);
    }
  else if (input == "_special2\n"){
    // change on timone audio
    digitalWrite(4, 1);
    digitalWrite(5, 1);
    myDFPlayer.volume(30);
    myDFPlayer.play(5);
    delay(5000);
  }
  else if (input == "_special3\n"){
    // change on timone audio
    digitalWrite(4, 1);
    digitalWrite(5, 1);
    myDFPlayer.volume(30);
    myDFPlayer.play(3);
    delay(5000);
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
