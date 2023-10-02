#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <SPI.h>
#include <RF24.h>

void setupTransmitter(void);
void sendData(int *, int *, int *);

#endif
