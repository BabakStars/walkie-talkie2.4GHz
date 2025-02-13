#include <RF24.h>
#include <SPI.h>
#include <RF24Audio.h>
#include <Wire.h>
#include <TM1637.h>
#include "printf.h"

RF24 radio(7,8);    // Set radio up using pins 7 (CE) 8 (CS)
RF24Audio rfAudio(radio,0); 


int Channel = 0;

TM1637 tm(A5, A4);

void setup() {      
  Serial.begin(115200);
  
  tm.begin();
  tm.setBrightnessPercent(90);
  tm.display("----");
  
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  
  
  printf_begin();
  radio.begin();
  rfAudio.begin();

  pinMode(3, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(3), talk, CHANGE);
  rfAudio.receive();
  
}


void talk()
{
  if(digitalRead(4) == LOW)
  {
    delay(50);
    Channel++;
    if(Channel > 125)
    {
      Channel = 125;
    }
    radio.setChannel(Channel);
    dis();
    
  }
  if(digitalRead(5) == LOW)
  {
    delay(50);
    Channel--;
    if(Channel < 0)
    {
      Channel = 0;
    } 
    radio.setChannel(Channel);
    dis();
  }
  
  
  if (!digitalRead(6)) 
  { 
    rfAudio.transmit();
  }
  else 
  {
    rfAudio.receive();
  }

}

void loop()
{
  
}
void dis()
{
   tm.display("    ");
   tm.display(Channel);
}
