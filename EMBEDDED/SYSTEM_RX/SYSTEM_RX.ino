#include "LORA.h"
#include <SPI.h>

#define reclen 64

LORA LR;

boolean SHIELD=true;

char recbuff[reclen];
char sendbuff[reclen];

char data[64];

int SF=11;
int BW=125;

int PWR=4;

void setup() 
{
  Serial.begin(9600);
  if (!LR.begin()) 
    {Serial.println("No LoRa module detected!");SHIELD=false;return;} 
  SX.setPower(PWR);
  Serial.println("Waiting for message...");
  LR.receiveMessMode();
}

void loop() 
{
  if (!SHIELD) {delay(100);return;}
  if (getMess()) {LR.receiveMessMode();}
}

boolean getMess()
{
  if (LR.dataRead(recbuff,reclen)<=0) {delay(100);return false;}
  Serial.println(recbuff);
  return true;
}
