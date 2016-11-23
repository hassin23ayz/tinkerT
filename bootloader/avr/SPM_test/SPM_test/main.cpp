/*
 * SPM_test.cpp
 * SPM mode means executing functions of <avr/boot.h> library. So can these function work 
   if we burn the code in the application section?
   
 1.	Project created at /avr named “SPM_test”. It’s a cpp project
 2.	Debug  will be added 
 3.	Will intentionally erase flash sections
 4.	Will burn the code at the application section [ there is an option in avr that there will be no BLS section we will choose it while burning]
 5.	I am looking forward to use avrdudes

 * Created: 11/23/2016 16:49:48
 * Author : Hassin
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "dbg_putchar.h"

int main(void)
{
	debug_output("SPM test on atmega328");
	debug_output("statement 1");
	_delay_ms(1000);
	debug_output("statement 2");
	_delay_ms(1000);
	debug_output("statement 3");
	_delay_ms(1000);
	debug_output("statement 4");
	_delay_ms(1000);
	debug_output("statement 5");
	_delay_ms(1000);	
    //while (1) 
    //{}
return 0;
}

