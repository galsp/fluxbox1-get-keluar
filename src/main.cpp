#include "lib.h"

// NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
void setup()
{
  Serial.begin(9600);
  setup2();
  modbusSetup();
}

void loop()
{
  printSensor();
  delay(100);
  if (Serial.available())
  {
    int intbuf1 = -1;
    int intbuf2 = -1;
    byte bufer[64];
    int len = Serial.readBytes(bufer, 64);
    for (int i = 0; i < len; i++)
    {

      if (bufer[i] == 112 && bufer[i + 1] == 105 && bufer[i + 2] == 110 && bufer[i + 3] == 103)
      {
        printping();
      }

      char charbuf = (char)bufer[i];
      String strbuf = String(charbuf);

      if (bufer[i - 1] == 40 && bufer[i + 1] == 44)
      {
        intbuf1 = strbuf.toInt();
      }
      else if (bufer[i - 1] == 44 && bufer[i + 1] == 41)
      {
        intbuf2 = strbuf.toInt();
      }
      if (bufer[i] == 41)
      {
        modbusRelay1(intbuf1, intbuf2);
        Serial.println("(" + String(intbuf1) + "," + String(intbuf2) + ")");
      }
    }
  }
}
