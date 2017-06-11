
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

#include "seriale.h"
