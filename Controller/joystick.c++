#include "include/joystick.hpp"

#define Pitch A0
#define Roll A1
#define Yaw A2

void readJoysticks(int *pPitch, int *pRoll, int *pYaw)
{
    *pPitch = analogRead(Pitch);
    *pRoll = analogRead(Roll);
    *pYaw = analogRead(Yaw);

    Serial.print("Pitch: ");
    Serial.print(*pPitch);
    Serial.print("Roll: ");
    Serial.print(*pRoll);
    Serial.print("Yaw: ");
    Serial.print(*pYaw);
    Serial.println();

    delay(200);
}