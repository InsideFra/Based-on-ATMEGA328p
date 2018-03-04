/*
 * Atmega328P.c
 *
 * Created: 25/02/2018 00:15:28
 * Author : franc
 */ 

#include <avr/io.h>
#include "Utilities/functions.h"

#define ButtonUP  0x0B// pin 5
#define ButtonDOWN 0x0B // pin 6
#define Speacker 0x0B // pin 7
#define INPUT 0
#define OUTPUT 1

int main(void)
{
	set_pin(ButtonUP, 5, INPUT, 0);
	set_pin(ButtonDOWN, 6, INPUT, 0);
    while (1) 
    {
		
    }
}

