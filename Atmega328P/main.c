/*
 * Atmega328P.c
 *
 * Created: 25/02/2018 00:15:28
 * Author : franc
 * Il programma è alla base del sistema Termostato-Wireless
 * È un concetto semplice e sicuramente ben sviluppato nell`industria moderna
 * Porta però con se nuovi concetti chiave come la codifica dei codici wireless
 * con token univoci rendendo impossibile l`hackeraggio da parte di man in the middle
 
 * Verrà sviluppato poi in seguito anche un programma che gestirà tutta le animazioni
 * dello schermo Oled, mantenendo al minimo l`utilizzo di memoria (compressione, azioni prestabilite)
 
 * Successivamente verranno rilasciati anche i sorgenti dell`hardware
 */ 

#include <avr/io.h>
#include "Utilities/functions.h"
#include "define.h"

extern int foo;

int main(void)
{
	set_pin(ButtonUP, 5, INPUT, 0);
	set_pin(ButtonDOWN, 6, INPUT, 0);
	set_pin(Speacker, 7, OUTPUT, 0);
	foo = 1;
    while (1) 
    {
		
    }
}

