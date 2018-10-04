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

uint8_t  bufferDataToWrite = 0;
uint32_t bufferDataToWrite32 = 0;
_Bool    bufferSize = 0; // 0 = 8bit, 1 = 32bit

uint32_t wRead_Register(uint8_t hexadress) {
	return 0;
}

/*
* Come funzione il wWrite_Registerx ?
* Esistono due funzioni, la funzione x = 8 e x = 32
* Nel caso di x = 8 -----> uint8_t hexadress =   Adress memoria del chip dove si vuole scrivere
*					-----> uint8_t datatowrite = Il valore che si vuole scrivere in quel registro
* La funzione, sendoverspi, accetta solo indirizzi di memoria di variabili a 32bit.
*                           il valore che noi passiamo � a 8bit
*
*
*
*/

void wWrite_Register8(uint8_t hexadress, uint8_t datatowrite) {
	set_pin(WCSN, 0, OUTPUT, 1); // Il pin CSN deve essere impostato come output HIGH per un giusta transazione
	toggle_pin(WCSN, 0); // Necessario per avviare una trasmissione nel chip.
    bufferDataToWrite = datatowrite; // Si "trasforma" la variabile datatowrite da 8bit in 32bit
		bufferSize = 0;
    sendoverspi(hexadress, 2); while(Sending) {}
}

void wWrite_Register32(uint8_t hexadress, uint32_t datatowrite, uint8_t buflengh) {

}

void startWireless() {
	if(SPCR & (1<<SPE)) { // Spi enabled
		//if(SPCR == wRegister) { // SPi set as i wanna
			wWrite_Register8(0b01000001, 0b01110111);
			while(!getstatus_pin(WCSN, 0)) { // Work in progress

			}
		//}
	} else {
		 spiconfig Spic = { 0, 0, 0, 0};
		 start_SPI(Spic);
		 startWireless();
    }
}

uint8_t wRead_Register8(uint8_t hexadress) {
	return 0;
}

uint32_t wRead_Register32(uint8_t hexadress) {
	return 0;
}

void setRX() {
	// PWR_UP 1 , PRIM_RX 1, CE 1
}

_Bool wSendPackage(uint8_t data) {
	return 0;
}
