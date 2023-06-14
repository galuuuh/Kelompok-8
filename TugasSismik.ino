#include <Servo.h>
#include <LiquidCrystal_I2C.h>
Servo CCTV;
const int kecepatan = 3;
const int pinTrigger = 10;
const int pinEcho = 11;
const int Keluaran = 8;
const int vcc = 5;
const int gnd = 7;
float durasi, jarak;
int posisi = 0;
bool bergerak = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(Keluaran, OUTPUT);
  pinMode(vcc, OUTPUT);
  pinMode(gnd, OUTPUT);
  digitalWrite(vcc, 1);
  digitalWrite(gnd, 0);
  CCTV.attach(12);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  // Ultrasonic dengan centimeter
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);

  durasi = pulseIn(pinEcho, HIGH);
  jarak = (durasi*.0343)/2;
  Serial.print("Jarak : ");
  Serial.println(jarak);
  
  //Mendeteksi cahaya
  int sensorCahaya = analogRead(A0);
  Serial.println(sensorCahaya);

  // Simulasi pergerakan CCTV
  if(sensorCahaya < 200){
    if(jarak < 10){                 // Ketika  ada benda sejauh 10cm dari sensor maka sensor akan berbunyi
        digitalWrite(Keluaran, 1);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ADA MALING!!!");
        lcd.setCursor(0, 1);
        lcd.print("Jarak");
        lcd.print(jarak);
        CCTV.write(posisi);
      }else{                        // Ketika tidak ada benda maka sensor akan terus bergerak
        lcd.clear();
        lcd.print("TIDAK ADA MALING...");
        digitalWrite(Keluaran, 0);
        if(bergerak == 0){
          if(posisi != 0){
            posisi -= kecepatan;
            CCTV.write(posisi);
          }else if(posisi == 0){
            posisi += kecepatan;
            CCTV.write(posisi);
            bergerak = 1;
          }
        }else{
          if(posisi != 180){
            posisi += kecepatan;
            CCTV.write(posisi);
          }else if(posisi == 180){
            posisi -= kecepatan;
            CCTV.write(posisi);
            bergerak = 0;
          }
        }
      }
  }else{
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("HARI MASIH CERAH");
    digitalWrite(Keluaran, 0);
    delay(20);
  }
  
}
