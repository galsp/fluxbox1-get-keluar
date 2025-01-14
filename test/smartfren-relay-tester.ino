#include "hendi-modbus-relay.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  modbusSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  modbusRelay1(1,0);
  modbusRelay1(1,1);
  modbusRelay1(1,2);
  modbusRelay1(1,3);
  modbusRelay1(1,4);
  modbusRelay1(1,5);
  modbusRelay1(1,6);
  modbusRelay1(1,7);
  modbusRelay2(1,0);
  modbusRelay2(1,1);
  modbusRelay2(1,2);
  modbusRelay2(1,3);
  modbusRelay2(1,4);
  modbusRelay2(1,5);
  modbusRelay2(1,6);
  modbusRelay2(1,7);
  delay(600*1000);
  modbusRelay1(0,0);
  modbusRelay1(0,1);
  modbusRelay1(0,2);
  modbusRelay1(0,3);
  modbusRelay1(0,4);
  modbusRelay1(0,5);
  modbusRelay1(0,6);
  modbusRelay1(0,7);
  modbusRelay2(0,0);
  modbusRelay2(0,1);
  modbusRelay2(0,2);
  modbusRelay2(0,3);
  modbusRelay2(0,4);
  modbusRelay2(0,5);
  modbusRelay2(0,6);
  modbusRelay2(0,7);
  delay(600*1000);
}
