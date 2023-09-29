#include "include/reciever.h"
#include "include/mpu.h"
#include "include/escCallibration.h"

int pitch = 0;
int roll = 0;
int yaw = 0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupReciever(void);
  setupESC(void)
}

void loop()
{
  // put your main code here, to run repeatedly:
  mainFunc(void);
  recieveData(&pitch, &roll, &yaw);
}
