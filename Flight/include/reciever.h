#ifndef RECIEVER_H
#define RECIEVER_H

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

void setupReciever(void);
void recieveData(int *, int *, int *);

#endif