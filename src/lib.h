#include <SoftwareSerial.h>
#include <NewPing.h>
const int trigPin = 32; // Pin Trig
const int echoPin = 33; // Pin Echo
#define MAX_DISTANCE 400
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);
void setup2()
{
  // Inisialisasi pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

unsigned long millise1;
unsigned long millise2;
bool detected = false;

// worked
#define softSerial_RX1 17
#define softSerial_TX1 16
//

bool relay_state_1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
bool relay_state_2[8] = {0, 0, 0, 0, 0, 0, 0, 0};

// SoftwareSerial RS485Serial(softSerial_RX, softSerial_TX);

byte DeviceID = 0x01;
byte ON_RELAY_1[8] = {DeviceID, 0x05, 0x00, 0x00, 0xFF, 0x00, 0x8C, 0x3A};
byte OFF_RELAY_1[8] = {DeviceID, 0x05, 0x00, 0x00, 0x00, 0x00, 0xCD, 0xCA};

byte ON_RELAY_2[8] = {DeviceID, 0x05, 0x00, 0x01, 0xFF, 0x00, 0xDD, 0xFA};
byte OFF_RELAY_2[8] = {DeviceID, 0x05, 0x00, 0x01, 0x00, 0x00, 0x9C, 0x0A};

byte ON_RELAY_3[8] = {DeviceID, 0x05, 0x00, 0x02, 0xFF, 0x00, 0x2D, 0xFA};
byte OFF_RELAY_3[8] = {DeviceID, 0x05, 0x00, 0x02, 0x00, 0x00, 0x6C, 0x0A};

byte ON_RELAY_4[8] = {DeviceID, 0x05, 0x00, 0x03, 0xFF, 0x00, 0x7C, 0x3A};
byte OFF_RELAY_4[8] = {DeviceID, 0x05, 0x00, 0x03, 0x00, 0x00, 0x3D, 0xCA};

byte ON_RELAY_5[8] = {DeviceID, 0x05, 0x00, 0x04, 0xFF, 0x00, 0xCD, 0xFB};
byte OFF_RELAY_5[8] = {DeviceID, 0x05, 0x00, 0x04, 0x00, 0x00, 0x8C, 0x0B};

byte ON_RELAY_6[8] = {DeviceID, 0x05, 0x00, 0x05, 0xFF, 0x00, 0x9C, 0x3B};
byte OFF_RELAY_6[8] = {DeviceID, 0x05, 0x00, 0x05, 0x00, 0x00, 0xDD, 0xCB};

byte ON_RELAY_7[8] = {DeviceID, 0x05, 0x00, 0x06, 0xFF, 0x00, 0x6C, 0x3B};
byte OFF_RELAY_7[8] = {DeviceID, 0x05, 0x00, 0x06, 0x00, 0x00, 0x2D, 0xCB};

byte ON_RELAY_8[8] = {DeviceID, 0x05, 0x00, 0x07, 0xFF, 0x00, 0x3D, 0xFB};
byte OFF_RELAY_8[8] = {DeviceID, 0x05, 0x00, 0x07, 0x00, 0x00, 0x7C, 0x0B};

// SoftwareSerial RS485Serial1(softSerial_RX1, softSerial_TX1);
// SoftwareSerial RS485Serial2(softSerial_RX2, softSerial_TX2);
// SoftwareSerial RS485Serial1();
// SoftwareSerial RS485Serial2();

byte *ON_RELAY[8] = {ON_RELAY_1, ON_RELAY_2, ON_RELAY_3, ON_RELAY_4, ON_RELAY_5, ON_RELAY_6, ON_RELAY_7, ON_RELAY_8};
byte *OFF_RELAY[8] = {OFF_RELAY_1, OFF_RELAY_2, OFF_RELAY_3, OFF_RELAY_4, OFF_RELAY_5, OFF_RELAY_6, OFF_RELAY_7, OFF_RELAY_8};

// EspSoftwareSerial::UART RS485Serial2;

void modbusSetup()
{
  Serial2.begin(9600, SERIAL_8N1, softSerial_RX1, softSerial_TX1);
  // RS485Serial2.begin(9600,SWSERIAL_8N1,softSerial_RX2,softSerial_TX2);
  // RS485Serial1.begin();
  // RS485Serial2.begin();
}

void printSensor()
{
  if (sonar.ping_cm() <= 100 && sonar.ping_cm() > 0)
  {
    millise2 = millis();
    if (millis() - millise1 > 200 && detected == false)
    {
      detected = true;
      Serial.println("{ \"ultrasonik\" : true }");
    }
    delay(100);
  }
  else if (sonar.ping_cm() > 100)
  {
    millise1 = millis();
    if (millis() - millise2 > 1500 && detected == true)
    {
      detected = false;
      Serial.println("{ \"ultrasonik\" : false }");
    }
    delay(100);
  }
}

void modbusRelay1(int _state, unsigned int _ord)
{
  unsigned long millisee = millis();
  bool bole = false;

  while (1)
  {
    if (_state == 0)
    {
      Serial2.write(OFF_RELAY[_ord], 8);
    }
    else
    {
      Serial2.write(ON_RELAY[_ord], 8);
    }
    delay(100);
    printSensor();
    relay_state_1[_ord] = _state;
    if (Serial2.available())
    {
      byte buffer[8];
      int len = Serial2.readBytes(buffer, 8);
      if (buffer[0] != 0)
      {
        Serial.println("{ \"relay\" : " + (String)_ord + ", \"status\" : " + (_state ? "ON" : "OFF") + " }");
        break;
      }
    }
    if (millis() - millisee > 5000 && bole == false)
    {
      bole = true;
      Serial.println("{ \"relay\" : " + (String)_ord + ", \"status\" : Wait }");
    }
  }
}
void printping()
{
  Serial.println("{ \"jarak\" : " + (String)sonar.ping_cm() + ", \"status\" : true }");
}
// void modbusRelay2(int _state, unsigned int _ord){
//   if(_state == 0){
//     RS485Serial2.write(OFF_RELAY[_ord],8); delay(200);
//   } else {
//     RS485Serial2.write(ON_RELAY[_ord],8); delay(200);
//   }
//   relay_state_2[_ord] = _state;
// }