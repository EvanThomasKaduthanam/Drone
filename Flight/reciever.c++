#include "include/reciever.h"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte Address[6] = "00009";

void setupReciever(void)
{
    radio.begin();
    radio.openReadingPipe(1, Address);
    Serial.println("Setup Reciever Done");
}

void recieveData(int *pPitch, int *pRoll, int *pYaw)
{

    radio.startListening();
    Serial.pirintln("listening");
    if (radio.available())
    {
        while (radio.available())
        {
            radio.read(pPitch, sizeof(*pPitch));
            radio.read(pRoll, sizeof(*pRoll));
            radio.read(pYaw, sizeof(*pYaw));
            Serial.println("Received Data : ");
            Serial.print("Pitch: ");
            Serial.print(*pPitch);
            Serial.print("Roll: ");
            Serial.print(*pRoll);
            Serial.print("Yaw: ");
            Serial.print(*pYaw);
            Serial.println();
        }
    }
    else
    {
        Serial.pirintln("Not listening");
    }
}