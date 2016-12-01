#include <SoftwareSerial.h>

SoftwareSerial debug(5,6); // RX[MOSI], TX[MISO]

#define LED_RED 14
#define LED_GREEN 15
#define REG_EN_PIN 3
#define GSM_SW_PIN 2

void pinsInit(void)
{
    pinMode(REG_EN_PIN, OUTPUT);
    pinMode(GSM_SW_PIN, OUTPUT);
    //giving the inactive stages at first
    digitalWrite(GSM_SW_PIN, LOW);   //active low(~)  //gsm SW on off pin is at high now 
    digitalWrite(REG_EN_PIN, LOW);   //active high  //regulator enable pin is at low noe
    delay(500);                      //for safety
}
void powerOn(void)
{
    digitalWrite(REG_EN_PIN, HIGH);  //power the module by enabling the regulator
    delay(100);                      //wait 100ms for stability of power reach
    digitalWrite(GSM_SW_PIN,HIGH);   //gsm SW on off pin is pulled down 
    delay(500);                      //for 500ms 
    digitalWrite(GSM_SW_PIN, LOW);   //gsm SW on off pin is pulled up again [by nternal resistor of modem]

    digitalWrite(LED_RED,LOW);      //LED notification
    digitalWrite(LED_GREEN,HIGH);
}

void powerOff(void)
{
   digitalWrite(GSM_SW_PIN,HIGH);   //gsm SW on off pin is pulled down 
   delay(500);                      //for 500ms 
   digitalWrite(GSM_SW_PIN, LOW);   //gsm SW on off pin is pulled up again [by nternal resistor of modem]
   delay(6000);                     //module needs this 6 sec time for power down routine and network disconnection
   digitalWrite(REG_EN_PIN,LOW);    //now turn off the main power by switching off the regulator

   digitalWrite(LED_GREEN,LOW);     //led notification
   digitalWrite(LED_RED,HIGH);  
}

uint8_t findSubString(char* mainStr, uint8_t mainLen, char* subStr, uint8_t subLen)
{  
  uint8_t ans = false;
  uint8_t count = 0;
  for(uint8_t i=0; i<mainLen; i++)
  {
    if(mainStr[i]== subStr[count])
      count++;
    else
      count = 0;
    if(count == (subLen-1))
    {
      ans = true;
      break;
    }
  }
  return ans; 
}

void setup() 
{
  debug.begin(9600);
  Serial1.begin(19200);
  
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_RED, OUTPUT);
  debug.println("initializing pins for Gsm module power control");
  pinsInit();
}

void loop() 
{ 
  /*
   * //ideal for sending AT commands to gsm Module directly
  if (debug.available()) 
  {
      Serial1.write(debug.read());
  }
  if (Serial1.available()) 
  {
    debug.write(Serial1.read());
  }*/
  if(debug.available()>0)
  {
    if(debug.read()=='1')
    {
      debug.print("you said: powerOnModule");
      powerOn();
    }
    else if(debug.read()=='0')
    {
      debug.print("you said: powerOffModule");
      powerOff();       
    }
    else if(debug.read()=='6')
    {
      debug.print("you queried: moduleStatus");
      Serial1.println("AT");
      delay(10);
      if(Serial1.available()>0)
      {
        char neowayReply[64];
        memset(neowayReply, '\0', 64);
        uint8_t i = 0; 
        while(Serial1.available()>0)
        {
          neowayReply[i++] = Serial1.read();
        }//fill incoming buffer

        if(findSubString(neowayReply, 128, "OK", 3))
        {
          debug.print("MODULE IS OK");
        }
        else
        {
          debug.print("could not understand what module said");
          digitalWrite(LED_GREEN,LOW);
          digitalWrite(LED_RED,HIGH);  
        }
      }//if serial available
      else
      {
        debug.print("module did not answer in 10ms");
      }
    }//if query cmd 6 came
  }//if any command got from debug port
}








