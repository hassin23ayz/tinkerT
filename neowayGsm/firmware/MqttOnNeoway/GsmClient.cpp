#include "GsmClient.h"

GsmClient::GsmClient()
{
	pinMode(REG_EN_PIN, OUTPUT);
	pinMode(GSM_SW_PIN, OUTPUT);
	//giving the inactive stages at first
	digitalWrite(GSM_SW_PIN, LOW);   //gsm SW on off pin is at high now as it is internally pulled up
	digitalWrite(REG_EN_PIN, LOW);   //regulator enable pin is at low now  
}

GsmClient::~GsmClient()
{}

bool GsmClient::init()
{
	return false;
}

bool GsmClient::init_onceautobaud()
{
	return false;
}

bool GsmClient::init_autobaud()
{
	return false;
}

bool GsmClient::init_fixbaud()
{
	return false;
}

bool GsmClient::setup()
{
	return false;
}

bool GsmClient::GetMyIP(char * ip)
{
	return false;
}

bool GsmClient::getIMEI(char * imei)
{
	return false;
}

bool GsmClient::isOn()
{
	return false;
}

bool GsmClient::isInitialized()
{
	return false;
}

bool GsmClient::isRegistered()
{
	return false;
}

bool GsmClient::isHttpInitialized()
{
	return false;
}

void GsmClient::powerOn()
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

void GsmClient::powerOff()
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

void GsmClient::send(const char * buf)
{
}

void GsmClient::cleanInput()
{
}

byte GsmClient::receive(char * buf)
{
	return byte();
}

byte GsmClient::receive(char * buf, uint16_t timeout)
{
	return byte();
}

bool GsmClient::receive(char * buf, uint16_t timeout, char const * checkok, char const * checkerror)
{
	return false;
}

bool GsmClient::ATcommand(const char * command, char * buf)
{
	return false;
}

bool GsmClient::ATcommand(const char * command, char * buf, char const * checkok, char const * checkerror, unsigned long timeout)
{
	return false;
}

bool GsmClient::TCPstart(const char * apn, const char * user, const char * pwd)
{
	return false;
}

bool GsmClient::TCPconnect(const char * server, int port)
{
	return false;
}

bool GsmClient::TCPGetMyIP(char * ip)
{
	return false;
}

bool GsmClient::TCPstop()
{
	return false;
}

void GsmClient::switchModem()
{
	digitalWrite(GSM_SW_PIN, HIGH);   //gsm SW on off pin is pulled down 
	delay(500);                      //for 500ms 
	digitalWrite(GSM_SW_PIN, LOW);   //gsm SW on off pin is pulled up again [by nternal resistor of modem]
}
