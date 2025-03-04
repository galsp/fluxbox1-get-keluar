// Pin konfigurasi
#include <Arduino.h>
#include <NewPing.h>
const int trigPin = 19; // Pin Trig
const int echoPin = 18; // Pin Echo
#define MAX_DISTANCE 400 

NewPing sonar(trigPin, echoPin, MAX_DISTANCE); 

// Variabel untuk menyimpan jarak
long duration;
float distance;

void setup() {
  // Inisialisasi pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Memulai komunikasi serial
  Serial.begin(9600);
}

void loop() {
  // Memastikan pin Trig rendah
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Mengirim sinyal HIGH selama 10 mikrodetik ke Trig
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Membaca durasi dari pin Echo
  duration = pulseIn(echoPin, HIGH);

  // Menghitung jarak dalam cm
  distance = duration * 0.034 / 2;

  // Menampilkan hasil di Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Delay agar pembacaan lebih stabil
  delay(500);
}
