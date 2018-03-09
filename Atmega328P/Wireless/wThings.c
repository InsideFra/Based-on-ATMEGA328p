/*
 * wThings.c
 *
 * Created: 25/02/2018 00:22:16
 *  Author: franc
 */ 

#include "wThings.h"
#include "../define.h"
#include <avr/io.h>
#include <string.h>
#include "../Utilities/functions.h"

extern uint8_t Sending;

uint32_t bufferDataToWrite = 0;

uint32_t wRead_Register(uint8_t hexadress) {
	return 0;
}

/*
* Come funzione il wWrite_Registerx ?
* Esistono due funzioni, la funzione x = 8 e x = 32
* Nel caso di x = 8 -----> uint8_t hexadress =   Adress memoria del chip dove si vuole scrivere
*					-----> uint8_t datatowrite = Il valore che si vuole scrivere in quel registro
* La funzione, sendoverspi, accetta solo indirizzi di memoria di variabili a 32bit.
*                           il valore che noi passiamo è a 8bit
*
*
*
*/

void wWrite_Register8(uint8_t hexadress, uint8_t datatowrite) {
	uint32_t bufferToSend = 0;
	bufferToSend = (uint32_t)(hexadress);  // Si "trasforma" la variabile hexadress da 8bit in 32bit
    bufferDataToWrite = (uint32_t)(datatowrite); // Si "trasforma" la variabile datatowrite da 8bit in 32bit
	bufferDataToWrite << 24; bufferToSend << 24;
	if(!Sending) {
		Sending = 2; 
        sendoverspi(&bufferToSend, 8);
	} 
}

void wWrite_Register32(uint8_t hexadress, uint32_t datatowrite, uint8_t buflengh) {
	
}

void startWireless() {
	// Check Vari
	if(SPCR & (1<<SPE)) { // Spi enabled
		if(SPCR == wRegister) { // SPi set as i wanna
			set_pin(WCSN, 0, OUTPUT, 1); // Il pin CSN deve essere impostato come output HIGH per un giusta transazione
			toggle_pin(WCSN, 0); // Necessario per avviare una transione nel chip.
			wWrite_Register8(0b01010000, 0b01110111);
			toggle_pin(WCSN, 0); // Necessario per interrompere una trasmissione nel chip.
		}
	} else start_SPI(PMosi, PMiso, PSckl, 0, 0, 0, 0); startWireless();
}