// joystick send by groundFungus aka c.goulding
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const byte CE_PIN = 9;
const byte CSN_PIN = 10;

const byte slaveAddress[5] = {'R', 'x', 'A', 'A', 'A'};

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

struct JoyValues
{
  int joy1x;
  int joy1y;
  int joy2x;
  int joy2y;
} joyValues;

unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000; // send once per second

const byte joy1xPin = A0;
const byte joy1yPin = A1;
const byte joy2xPin = A2;
const byte joy2yPin = A3;

void setup()
{

  Serial.begin(115200);
  Serial.println("Transmitter Starting");

  radio.begin();
  radio.setChannel(76); // 76 library default
  // RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(3, 5); // delay, count
  radio.openWritingPipe(slaveAddress);
  radio.stopListening();
}

void loop()
{
  currentMillis = millis();
  if (currentMillis - prevMillis >= txIntervalMillis)
  {
    send();
    Serial.print("JOY 1 X = ");
    Serial.print(joyValues.joy1x);
    Serial.print("  JOY 1 Y = ");
    Serial.print(joyValues.joy1y);
    Serial.print("  JOY 2 X = ");
    Serial.print(joyValues.joy2x);
    Serial.print("  JOY 2 Y = ");
    Serial.println(joyValues.joy2y);
    prevMillis = millis();
  }
}

//====================

void send()
{
  joyValues.joy1x = analogRead(joy1xPin);
  joyValues.joy1y = analogRead(joy1yPin);
  joyValues.joy2x = analogRead(joy2xPin);
  joyValues.joy2y = analogRead(joy2yPin);
  radio.write(&joyValues, sizeof(joyValues));
}