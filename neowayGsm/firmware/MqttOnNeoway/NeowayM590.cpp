#include "NeowayM590.h"


// check presence of str2 in str1
bool found( const char * buf, const char * check )
{
  if (!check) {
    return false;
  }
  return strstr(buf, check);
}


NeowayM590::NeowayM590()
{}


NeowayM590::~NeowayM590()
{}


//NOTE:if returns true then you can work with neoway module 
bool NeowayM590::init()
{
	pinMode(REG_EN_PIN, OUTPUT);
	pinMode(GSM_SW_PIN, OUTPUT);
	//giving the inactive stages at first
	digitalWrite(GSM_SW_PIN, LOW);   //gsm SW on off pin is at high now as it is internally pulled up
	digitalWrite(REG_EN_PIN, LOW);   //regulator enable pin is at low now
	
    bool autoBaud = false;
    unsigned int startTime = millis();
	do
	{
	  autoBaud = init_autobaud();
	  if(!autoBaud) 
	  {
	  	 //LOG:bps not ok
	     bool fixBaud = init_fixbaud();
	     if(!fixBaud) 
	     {
	       //LOG:auto fix bps failed : modem may be not powered up
	       switchOn();
	       delay(500);
	     }
	  }
	}
  while((autoBaud != true) && (millis()-startTime < 10000));
  return autoBaud;
}

bool NeowayM590::init_autobaud()
{
	state = STATE_NONE;
	Serial1.begin(19200);

	byte i = 1;
	do
	{
		if(init_onceautobaud())
		{
		  //LOG:AT responded OK at init_onceautobaud()
		  //LOG:modem initialized
		  state |= STATE_INITIALIZED;
		  return true;
		}
		delay(2000);
	} while (i++ < 3 && !isInitialized());
	return false;
}

bool NeowayM590::init_onceautobaud()
{
  char buf[BUF_LENGTH];
  cleanInput();
  if (ATcommand("", buf))
  {
    //AT command responded OK
    return true;
  }
    //LOG:AT command  failed
  return false;
}

bool NeowayM590::init_fixbaud()
{
  char buf[BUF_LENGTH];
  char command[BUF_LENGTH];

  //LOG:fixing autobaud

  // try different fixed baud rate
  long int baudrate []={19200,9600,14400,38400,57600,115200};

  for (byte i=0; (i<(sizeof(baudrate) / sizeof(long int))); i++) 
  {
    cleanInput();
    //LOG:trying with baudrate:
    //LOG:Serial.println(baudrate[i]

    Serial1.begin(baudrate[i]);

    if (ATcommand("", buf))
    {
      //LOG:baudrate found      
      //LOG:baudrate[i]
      sprintf(command,"+IPR=%ld",baudrate[i]);
      if (ATcommand(command, buf))
      {
	       //LOG:saving baud settings in profile
	       if (!ATcommand("&W", buf))
            return false;
	       if (!ATcommand("+IPR=0", buf)) //set autobaud feature
	        return false;   
	      state |= STATE_INITIALIZED;
	      return true;
      }
    }
  }
  state &= ~STATE_INITIALIZED;
  //LOG: modem inizialization failed")));
  return false;
}

bool NeowayM590::setup()
{
	return false;
}

bool NeowayM590::GetMyIP(char * ip)
{
	return false;
}

bool NeowayM590::getIMEI(char * imei)
{
	return false;
}

bool NeowayM590::isOn()
{
	return false;
}

bool NeowayM590::isInitialized()
{
	return false;
}

bool NeowayM590::isRegistered()
{
	return false;
}

bool NeowayM590::isHttpInitialized()
{
	return false;
}

void NeowayM590::powerOn()
{
	digitalWrite(REG_EN_PIN, HIGH);  //power the module by enabling the regulator
	delay(100);                      //wait 100ms for stability of power reach
	digitalWrite(GSM_SW_PIN, HIGH);   //gsm SW on off pin is now made Low 
	delay(500);                      //keep the pin Low for 500ms 
	digitalWrite(GSM_SW_PIN, LOW);   //make gsm SW on off pin pulled up again 

									 //Now neoway gsm module should power up now and +PBREADY type msg should come from neoway
#if DEBUG
	digitalWrite(LED_RED, LOW);      //LED notification
	digitalWrite(LED_GREEN, HIGH);
#endif // DEBUG
}

void NeowayM590::powerOff()
{
	digitalWrite(GSM_SW_PIN, HIGH);   //gsm SW on off pin is pulled down 
	delay(500);                      //for 500ms 
	digitalWrite(GSM_SW_PIN, LOW);   //gsm SW on off pin is pulled up again [by nternal resistor of modem]
	delay(6000);                     //module needs this 6 sec time for power down routine and network disconnection
	digitalWrite(REG_EN_PIN, LOW);    //now turn off the main power by switching off the regulator

#if DEBUG
	digitalWrite(LED_GREEN, LOW);     //led notification
	digitalWrite(LED_RED, HIGH);
#endif // DEBUG
}

void NeowayM590::send(const char * buf)
{
}

void NeowayM590::cleanInput()
{
}

byte NeowayM590::receive(char * buf)
{
	return byte();
}

byte NeowayM590::receive(char * buf, uint16_t timeout)
{
	return byte();
}

bool NeowayM590::receive(char * buf, uint16_t timeout, char const * checkok, char const * checkerror)
{
	return false;
}

bool NeowayM590::ATcommand(const char * command, char * buf)
{
	return false;
}

bool NeowayM590::ATcommand(const char * command, char * buf, char const * checkok, char const * checkerror, unsigned long timeout)
{
	return false;
}

bool NeowayM590::TCPstart(const char * apn, const char * user, const char * pwd)
{
	return false;
}

bool NeowayM590::TCPconnect(const char * server, int port)
{
	return false;
}

bool NeowayM590::TCPGetMyIP(char * ip)
{
	return false;
}

bool NeowayM590::TCPstop()
{
	return false;
}

void NeowayM590::switchModem()
{
	digitalWrite(GSM_SW_PIN, HIGH);   //gsm SW on off pin is pulled down 
	delay(500);                      //for 500ms 
	digitalWrite(GSM_SW_PIN, LOW);   //gsm SW on off pin is pulled up again [by nternal resistor of modem]
}
