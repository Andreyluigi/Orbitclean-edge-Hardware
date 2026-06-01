#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const int PIN_TRIG = 12;
const int PIN_ECHO = 11;
const int PIN_BUZZER = 13;
const int PIN_TEMP = A0;

const int LED_VERMELHO = A1;
const int LED_AMARELO   = A2;
const int LED_VERDE     = A3;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo propulsorX;
Servo propulsorY;

void alternarPainelLEDs(bool red, bool yellow, bool green) {
  digitalWrite(LED_VERMELHO, red ? HIGH : LOW);
  digitalWrite(LED_AMARELO, yellow ? HIGH : LOW);
  digitalWrite(LED_VERDE, green ? HIGH : LOW);
}

void setup() {
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  
  propulsorX.attach(9);
  propulsorY.attach(10);
  
  propulsorX.write(90);
  propulsorY.write(90);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("OrbitClean Edge");
  lcd.setCursor(0, 1);
  lcd.print("Sistemas OK...");
  
  alternarPainelLEDs(true, true, true);
  delay(1500);
  alternarPainelLEDs(false, false, false);
}

void loop() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  
  long duracao = pulseIn(PIN_ECHO, HIGH);
  float distancia_cm = duracao * 0.0343 / 2;
  
  int leitura_analogica = analogRead(PIN_TEMP);
  float beta = 3950;
  float temperatura_c = 1.0 / (log(1.0 / (1023.0 / leitura_analogica - 1.0)) / beta + 1.0 / 298.15) - 273.15;
  
  lcd.clear();
  
  if (distancia_cm > 150.0) {
    alternarPainelLEDs(false, false, true);
    
    noTone(PIN_BUZZER);
    propulsorX.write(90); 
    propulsorY.write(90);
    
    lcd.setCursor(0, 0);
    lcd.print("STATUS: SECURE");
    lcd.setCursor(0, 1);
    lcd.print("T:");
    lcd.print(temperatura_c, 1);
    lcd.print("C R:");
    lcd.print(distancia_cm, 0);
    lcd.print("cm");
    
  } else if (distancia_cm <= 150.0 && distancia_cm > 50.0) {
    alternarPainelLEDs(false, true, false);
    
    tone(PIN_BUZZER, 1000);
    delay(80);
    noTone(PIN_BUZZER);
    
    lcd.setCursor(0, 0);
    lcd.print("WARN: DETRITUS");
    lcd.setCursor(0, 1);
    lcd.print("DIST: ");
    lcd.print(distancia_cm, 1);
    lcd.print("cm");
    
  } else {
    alternarPainelLEDs(true, false, false);
    
    tone(PIN_BUZZER, 2200); 
    propulsorX.write(45);  
    propulsorY.write(135); 
    
    lcd.setCursor(0, 0);
    lcd.print("ALERTA ERRO 1202");
    lcd.setCursor(0, 1);
    lcd.print("EVASAO ATIVA AXIS");
  }
  
  delay(400); 
}
