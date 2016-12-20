#include "Arduino.h"

#ifndef UNIT_TEST

#define BLINKPIN 13

void initBlink(void)
{
	pinMode(BLINKPIN,OUTPUT);
}

void doBlink(int i)
{
	if(i == 1)
	{
		digitalWrite(BLINKPIN, HIGH);
		delay(1000);
		digitalWrite(BLINKPIN, LOW);
		delay(1000);
	}
}

void setup()
{
	initBlink();
}

void loop()
{
	doBlink(1);
}

#endif
