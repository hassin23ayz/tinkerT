#pragma once

#include "Arduino.h"
#include <Time.h>
#include "IPAddress.h"
#include <SoftwareSerial.h>

#define DEBUG 0

#if DEBUG
#define LED_RED 14
#define LED_GREEN 15  
#endif // DEBUG

//gsm module power control pins 
#define REG_EN_PIN 3    //active high
#define GSM_SW_PIN 2    //active Low(~)

#define BUF_LENGTH 100
#define BUFCOMMAND_LENGTH 120

#define STATE_NONE 0
#define STATE_ON 1
#define STATE_INITIALIZED 2
#define STATE_REGISTERED 4
#define STATE_HTTPINITIALIZED 8

#define ATSTR  "AT"
#define OKSTR  "OK\r\n"
#define ERRORSTR  "ERROR\r\n"

class GsmClient
{
public:
	GsmClient();
	~GsmClient();

	bool init();
	bool init_onceautobaud();
	bool init_autobaud();
	bool init_fixbaud();
	bool setup();

	bool GetMyIP(char*ip); // ip no less 15 char + terminator
	bool getIMEI(char *imei); // imei no less 15 char + terminator

	bool isOn();
	bool isInitialized();
	bool isRegistered();
	bool isHttpInitialized();

	void powerOn();
	void powerOff();

	void send(const char *buf);
	void cleanInput();
	byte receive(char *buf);
	byte receive(char *buf, uint16_t timeout);
	bool receive(char *buf, uint16_t timeout, char const *checkok, char const *checkerror);
	bool ATcommand(const char *command, char *buf);
	bool ATcommand(const char *command, char *buf, char const *checkok, char const *checkerror, unsigned long  timeout);

	bool TCPstart(const char *apn, const char *user, const char *pwd);
	bool TCPconnect(const char* server, int port);
	bool TCPGetMyIP(char*ip);
	bool TCPstop();

	byte state;

private:
	void switchModem();
	//byte regEnPin;
	//byte gsmSwPin;
};







