#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const byte CE_PIN = 9;
const byte CSN_PIN = 10;

const byte thisSlaveAddress[5] = {'R', 'x', 'A', 'A', 'A'};

RF24 radio(CE_PIN, CSN_PIN);

struct JoyValues
{
  int joy1x;
  int joy1y;
  int joy2x;
  int joy2y;
} joyValues;

bool newData = false;

//===========

void setup()
{

  Serial.begin(115200);

  Serial.println("Reciever Starting");

  radio.begin();
  radio.setChannel(76);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, thisSlaveAddress);
  radio.startListening();
}

//=============

void loop()
{
  getData();
  showData();
}

//==============

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
    Serial.print("JOY 1 X = ");
    Serial.print(joyValues.joy1x);
    Serial.print("  JOY 1 Y = ");
    Serial.print(joyValues.joy1y);
    Serial.print("  JOY 2 X = ");
    Serial.print(joyValues.joy2x);
    Serial.print("  JOY 2 Y = ");
    Serial.println(joyValues.joy2y);
    delay(1000);
    newData = false;
  }
}
