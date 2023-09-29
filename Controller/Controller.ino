#include "include/joystick.h"
#include "include/transmitter.h"

int pitch = 0;
int roll = 0;
int yaw = 0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  setupTransmitter();
}

void loop()
{
  // put your main code here, to run repeatedly:
  readJoysticks(&pitch, &roll, &yaw);

  sendData(&pitch, &roll, &yaw);
}
