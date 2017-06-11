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
    Serial.println("Valvole");
  }
  if (!sign_generatore){
    Serial.println("Generatore");
  }
  if (!sign_motore){
    Serial.println("Motore");
  }
  if (!sign_interruttori){
    Serial.println("Interruttori");
  }
  if (!sign_stereo){
    Serial.println("Stereo");
  }
  if(!sign_culla){
    Serial.println("Culla");
  }
  if(!sign_croce){
    Serial.println("Croce");
  }
  if(!sign_foto){
    Serial.println("Foto");
  }
  if(!sign_timone){
    Serial.println("Timone");
  }
  if(!sign_orologi){
    Serial.println("Orologi");
  }
  if(!sign_organo){
    Serial.println("Organo");
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
    Serial.println("Gamers goes to the second floors!");
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
    
    // organo
    digitalWrite(organo, HIGH);
    delay(200);
    }
  // open all
  else if (input == "_openAll\n"){
    // open all the doors
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
    digitalWrite(M3, LOW);
    delay(100);
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
    Serial.println("\nOpened all");
  }
  // Mano
  else if (input == "_mano\n") {
    Serial.println("\nAttivo mano");
    digitalWrite(mano, HIGH);
    delay(12000);
    digitalWrite(mano, LOW);
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
    Serial.println("\nGiochi risolti:");
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
