#include "include/joystick.h"

#define Pitch A1
#define Roll A2
#define Yaw A3

void readJoysticks(int *pPitch, int *pRoll, int *pYaw)
{
    *pPitch = analogRead(Pitch);
    *pRoll = analogRead(Roll);
    *pYaw = analogRead(Yaw);

    // Serial.print("Pitch: ");
    // Serial.print(*pPitch);
    // Serial.print("Roll: ");
    // Serial.print(*pRoll);
    // Serial.print("Yaw: ");
    // Serial.print(*pYaw);
    // Serial.println();

    delay(200);
}