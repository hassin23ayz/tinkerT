#include "NeowayM590.h"



NeowayM590::NeowayM590()
{
}


NeowayM590::~NeowayM590()
{
}

bool NeowayM590::init()
{
	return false;
}

bool NeowayM590::init_onceautobaud()
{
	return false;
}

bool NeowayM590::init_autobaud()
{
	return false;
}

bool NeowayM590::init_fixbaud()
{
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
}

void NeowayM590::powerOff()
{
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
}
