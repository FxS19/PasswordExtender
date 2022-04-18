//Modifizierte Version von DigiStump verwendet
#define LAYOUT_GERMAN //https://github.com/rsrdesarrollo/DigistumpArduino
#include "DigiKeyboard.h"
#include <EEPROM.h>

#define LEDPIN 1
#define BUTTONLONG 500
#define BUTTON 2         // Short to gnd with a button to toggle the jiggler state
#define PWLENGTH 20
#define SECRETADDRESS 1

uint8_t ctr = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  digitalWrite(LEDPIN, HIGH);
  delay(100);
  digitalWrite(LEDPIN, LOW);
  delay(150);
  digitalWrite(LEDPIN, HIGH);
  delay(100);
  digitalWrite(LEDPIN, LOW);
  DigiKeyboard.sendKeyStroke(0);
}

void loop() {
  button();
}


void writePW(){
  int secret = (EEPROM.read(SECRETADDRESS + 1) << 8);
  secret |= EEPROM.read(SECRETADDRESS);
  
  const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890*-+/!?%&=~_.,@#";
  randomSeed(secret + ctr);
  for (uint8_t i = 0; i < PWLENGTH; i++){
    DigiKeyboard.print(charset[random(sizeof(charset)-1)]);
  }
  DigiKeyboard.println("");
  for (uint8_t i = 0; i < PWLENGTH + 1; i++){
    DigiKeyboard.sendKeyStroke(0x2A);
  }
  ctr = 0;
}

void button () {
  static unsigned long lasthigh = 0;
  static unsigned long lastedge = 0;
  unsigned long nowms;
  int state;
  static int oldstate = LOW;
  state = digitalRead(BUTTON);
  nowms = millis();
  //
  if (state == LOW && oldstate == HIGH) {  // butten was pressed
    lastedge = nowms;
  }

  if (state == HIGH && oldstate == LOW && nowms - lastedge > 20) {
    if (nowms - lastedge < BUTTONLONG) {
      ctr++;
    } else if (nowms - lastedge < 30000) {
      writePW();
    } else{
      writeSecret();
    }
  }
  oldstate = state;
}

void writeSecret() {
  for(int i = 0; i < 30; i++) {
    digitalWrite(LEDPIN, HIGH);
    delay(100);
    digitalWrite(LEDPIN, LOW);
    delay(150);
  }
  int oldsecret = (EEPROM.read(SECRETADDRESS + 1) << 8);
  oldsecret |= EEPROM.read(SECRETADDRESS);
  int value = millis() + oldsecret;
  EEPROM.write(SECRETADDRESS, value);
  EEPROM.write(SECRETADDRESS + 1, value >> 8);
}
