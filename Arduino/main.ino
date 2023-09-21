#include "headers/sensor.h"
#include "headers/esp.h"

void setup()
{
    checkMPU6050();
    checkESP();
}

void loop()
{
    getAccelValues();

    getGyroValues();
}