#include <SoftwareSerial.h>

SoftwareSerial debug(5,6); // RX[MOSI], TX[MISO]

#define LED_RED 14
#define LED_GREEN 15

#define REG_EN_PIN 3    //active high
#define GSM_SW_PIN 2    //active Low(~)

#define SIZE_NEOWAY_OK 3
#define SIZE_RESPONSE 64


void pinsInit(void)
{
    pinMode(REG_EN_PIN, OUTPUT);
    pinMode(GSM_SW_PIN, OUTPUT);
    //giving the inactive stages at first
    digitalWrite(GSM_SW_PIN, LOW);   //gsm SW on off pin is at high now as it is internally pulled up
    digitalWrite(REG_EN_PIN, LOW);   //regulator enable pin is at low noe
    delay(500);                      //for safety
}
void powerOn(void)
{
    digitalWrite(REG_EN_PIN, HIGH);  //power the module by enabling the regulator
    delay(100);                      //wait 100ms for stability of power reach
    digitalWrite(GSM_SW_PIN,HIGH);   //gsm SW on off pin is now made Low 
    delay(500);                      //keep the pin Low for 500ms 
    digitalWrite(GSM_SW_PIN, LOW);   //make gsm SW on off pin pulled up again 

    //Now neoway gsm module should power up now and +PBREADY type msg should come from neoway
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

bool findSubString(char* mainStr, uint8_t mainLen, char* subStr, uint8_t subLen)
{  
  bool ans = false;
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

bool sendATcommand(char* ATcommand, unsigned long timeout)
{  
  uint8_t n=0;
  bool ans = false;
  char response[SIZE_RESPONSE];
  memset(response,'\0',SIZE_RESPONSE);
  unsigned long previous = 0;
  
  n=0;  
  previous = millis();
  Serial1.flush();               
  Serial1.println(ATcommand);    // Send the AT command
  do                             // this loop waits for the answer until timeouts
  {
    if(Serial1.available() > 0)
    {
      char c = Serial1.read();
      if (c != -1)
      {
        response[n] = c;
        n = ((n+1) % SIZE_RESPONSE);
        if (findSubString((char*)response,SIZE_RESPONSE, "OK", SIZE_NEOWAY_OK))
        {
          ans = true;
          break;
        }
      }
    }
  }
  while((unsigned long)(millis() - previous) < timeout); 
  return ans;  
}



void setup() 
{
  debug.begin(19200);
  Serial1.begin(19200);
  
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinsInit();
  debug.println("Gsm module power control pins initialized");
}

void loop() 
{ 
  //ideal for sending AT commands to gsm Module directly
  if (debug.available()) 
  {
      Serial1.write(debug.read());
  }
  if (Serial1.available()) 
  {
    debug.write(Serial1.read());
  }
  if(debug.available()>0)
  {
    char ch = (char)debug.read();
    if(ch=='1')
    {
      debug.println("you said: powerOnModule");
      powerOn();
    }
    else if(ch=='0')
    {
      debug.println("you said: powerOffModule");
      powerOff();       
    }
    else if(ch=='6')
    {
      debug.println("you queried: moduleStatus");
      bool isModuleOn = sendATcommand("AT", 2000);
      if(isModuleOn)
        debug.println("neoway is powered On");
      else
        debug.println("neoway Off");           
    }//if query cmd 6 came
  }//if any command got from debug port
}








