#include <Servo.h>
Servo myservo;
const int PinTrigger = 10;
const int PinEcho = 11;
const int Keluaran = 8;
float durasi, jarak;
bool bergerak = 1;
int posisi = 0;
int SensorCahaya = analogRead(A0);

void setup() {
  pinMode(PinTrigger, OUTPUT);
  pinMode(PinEcho, INPUT);
  pinMode(Keluaran, OUTPUT);
  myservo.attach(12);
}

void loop() {

  digitalWrite(Keluaran, 0);

  //Membuat sensor ULtrasonic mengukur dalam satuan cm
  digitalWrite(PinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(PinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(PinTrigger, LOW);

  durasi = pulseIn(PinEcho, HIGH);
  jarak = (durasi*.0343)/2;
  Serial.print("Jarak : ");
  Serial.println(jarak);

  //Membuat program aktif jika sensor cahaya mengukur < 200 atau masuk dalam keadaan gelap
  if(SensorCahaya < 200){
    if(jarak < 10){
      // Jika sensor ultrasonic mendeteksi ada bedan didepannya sejauh < 10 cm maka keluaran akan HIGH
      digitalWrite(Keluaran, 1);
    }else{
      // Jika sensor ultrasonic tidak mendeteksi servo akan bergerak dengan kode dibawah
      digitalWrite(Keluaran, 0);
      if(bergerak == 1){
        if(posisi += 0){
          posisi -= 30;
          myservo.write(posisi);
        }else if(posisi == 0){
          posisi += 30;
          myservo.write(posisi);
          bergerak = 0;
        }
      }else{
        if(posisi != 180){
          posisi += 30;
          myservo.write(posisi);
        }else if(posisi == 180){
          posisi -= 30;
          myservo.write(posisi);
          bergerak = 1;
        }
      }
    }
  }else{
    digitalWrite(Keluaran, 0);
    delay(20);
  }
}
