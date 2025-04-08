// F1SSF Arduino I U Monitoring for PA and others bis
// use with APM Power Module GM V1.0  (U image=1/10 de V Alim  et I image=70mV * A) 
// Code from: 07/03/2023.   Release from: 25/03/2023
// Hardware: Arduino 2560 + LCD 4L 20C + I2C module
// sur UNO, les broches SDA et SCL sont respectivement A4 et A5  

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // initialisation de l'afficheur LCD

const int pinA = A0; // broche analogique pour la première tension
const int pinB = A1; // broche analogique pour la deuxième tension image du courant

void setup() {
  Serial.begin(9600); // initialisation de la communication série
  lcd.init(); // initialisation de l'afficheur LCD
  lcd.backlight(); // allumage du rétroéclairage
  lcd.clear(); // effacement de l'écran
}

void loop() {
  // lecture des tensions analogiques
  int valA = analogRead(pinA);
  int valB = analogRead(pinB);

  // conversion des valeurs analogiques en volts
  // float voltageA = valA * 50.0 / 1023.0;    >>>>  convertion de 1/10 de U Alim
  // float voltageB = valB * 160.0 / 1023.0;   >>>> convertion courant /puissance
  // float voltageB = valB * 160.0 / 1023.0;   >>>> convertion U RF /puissance
  float voltageA = valA * 50.0 / 1023.0;
  float voltageB = valB * 160.0 / 1023.0;

  // affichage des tensions sur l'afficheur LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Monitoring PA 10 Ghz ");
  lcd.setCursor(0,2);
  lcd.print("  U Alim:  ");
  lcd.print(voltageA);
  lcd.print(" V");
  lcd.setCursor(0,3);
  lcd.print("  Power :  ");
  lcd.print(voltageB);
  lcd.print(" W");

  // conditions de passage TX et RX + alarm PA
  lcd.setCursor(0, 1);   
  if (voltageB>1 && voltageB<8)
    lcd.print("Radio TX ");  
  else
    lcd.print("Radio RX");

  lcd.setCursor(10, 1);   
  if (voltageB>=0 && voltageB<=8)
    lcd.print("ALARM OFF ");  
  else
    lcd.print("ALARM ON");

  delay(2000); // attente d'une seconde avant de répéter la lecture
}
