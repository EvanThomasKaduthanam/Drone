#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

void setupTransmitter(void);
void sendData(int *, int *, int *);