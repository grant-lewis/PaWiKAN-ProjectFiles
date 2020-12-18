#include <LORA.h>
#include <SPI.h>
#include "HX711.h"

#define calibration_factor -7050.0

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2
#define psound 9
#define pingo 19
#define pinf  7

#define RXTIMEOUT 500

LORA LR;



HX711 scale;

char inpbuff[64];

char data[64];

int SF=11;
int BW=125;

int PWR=4;

int trigPin = 3;    // Trigger
int echoPin = 2;    // Echo
long duration;
int cm, inches;
int STP = 4; 
int DIR = 3; 
int delay_ms = 100;
int delay_time = 1000;
boolean SHIELD=true;

void setup() 
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pingo,INPUT_PULLUP);
  digitalWrite(pinf,0);
  pinMode(pinf,OUTPUT);
  pinMode(psound,OUTPUT);
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare();
  if (!LR.begin()) 
    {Serial.println("No LoRa module detected!");SHIELD=false;return;}
  SX.setPower(PWR);
}

void loop() 
{
  if (!SHIELD) return;
  memset(inpbuff, 0, sizeof(inpbuff));
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2) / 29.1;
  strcat(inpbuff, "Tension value (in lbs): ");
  char * tension;
  dtostrf(scale.get_units(), 0, 1, tension);
  strcat(inpbuff, tension);
  strcat(inpbuff, ", Proximity: (in cm): ");
  char * ultrasonic;
  dtostrf(cm, 0, 1, ultrasonic);
  strcat(inpbuff, ultrasonic);

  if(scale.get_units() > 3.0) {
      digitalWrite(DIR,LOW);
      while(scale.get_units() > 2.5) {
        digitalWrite(STP,HIGH); 
        delayMicroseconds(delay_ms); 
        digitalWrite(STP,LOW); 
        delayMicroseconds(delay_ms); 
      }
  }
      
  if(scale.get_units() < 2.0) {
      digitalWrite(DIR,HIGH);
      while(scale.get_units() < 2.5) {
        digitalWrite(STP,HIGH); 
        delayMicroseconds(delay_ms); 
        digitalWrite(STP,LOW); 
        delayMicroseconds(delay_ms); 
      }
  }

  if(scale.get_units() > 6.0) {
    strcat(inpbuff, ", Overload!");
  }

  sendBuff();
}




void sendBuff()
{
  digitalWrite(pinf,LOW);
  Serial.println(inpbuff);
  char f=LR.sendMess(inpbuff); 
  if (f<0) Serial.println("Error in transmission!");
  SX.setState(STDBY);
}
