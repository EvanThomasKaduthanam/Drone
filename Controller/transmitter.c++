// #include <SPI.h>
// #include <RF24.h>

// RF24 radio(7, 8); // CE CSN
// const byte Address[6] = "00009";

// void setupTransmitter(void)
// {
//     radio.begin();
//     radio.openWritingPipe(Address);
// }

// void sendData(int *pPitch, int *pRoll, int *pYaw)
// {

//     radio.stopListening(); // set as transmitter
//     // int value = analogRead(pot_pin);
//     // int data = map(value, 0, 1023, 0, 255); // Converting 10bit to 8bit
//     radio.write(pPitch, sizeof(*pPitch));
//     radio.write(pRoll, sizeof(*pRoll));
//     radio.write(pYaw, sizeof(*pYaw));
//     Serial.print("Transmitting Data : ");
//     Serial.println(*pPitch, *pRoll, *pYaw);
// }
// Include Libraries
