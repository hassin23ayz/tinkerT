#include <SoftwareSerial.h>

SoftwareSerial debug(5,6); // RX[MOSI], TX[MISO]

void setup() 
{
  pinMode(14, OUTPUT); 
  digitalWrite(14, HIGH);
  pinMode(15, OUTPUT); 
  
  // set the data rate for the SoftwareSerial port
  debug.begin(9600);
  debug.println("Hello I am Debug");
}

void loop() 
{ 
  if (debug.available()>0) 
  {
    digitalWrite(15, HIGH);
    delay(100);
    uint8_t i = 0;
    char inMsg[128];
    memset(inMsg,'\0',128);
    while(debug.available()!=0)
          inMsg[i++]=debug.read();
          
    debug.print("you said:");
    debug.println(inMsg);
  }
}

