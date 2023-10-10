#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "include/variables.h"
#include "include/receiver.h"

const byte CE_PIN = 9;
const byte CSN_PIN = 8;

const byte thisSlaveAddress[5] = {'D', 'r', 'o', 'N', 'E'};

RF24 radio(CE_PIN, CSN_PIN);

bool newData = false;

//===========

void setupRecv()
{

    Serial.println("Reciever Starting");

    if (radio.begin())
    {
        Serial.println("Receiver began");
    }
    else
    {
        Serial.println("Receiver not working");
    }
    radio.setChannel(115);
    radio.setDataRate(RF24_250KBPS);
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.startListening();
}

void getData()
{
    if (radio.available())
    {
        radio.read(&joyValues, sizeof(joyValues));
        newData = true;
    }
}

void showData()
{
    if (newData == true)
    {
        Serial.print("Data received >> ");
        Serial.print("Throttle = ");
        Serial.print(joyValues.throttle);
        Serial.print(" Yaw = ");
        Serial.print(joyValues.yaw);
        Serial.print("  Pitch = ");
        Serial.print(joyValues.pitch);
        Serial.print("  Roll = ");
        Serial.println(joyValues.roll);
        delay(1000);
        newData = false;
    }
}
