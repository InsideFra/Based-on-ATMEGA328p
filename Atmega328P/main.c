/*
 * Atmega328P.c
 *
 * Created: 25/02/2018 00:15:28
 * Author : franc
 * Il programma � alla base del sistema Termostato-Wireless
 * � un concetto semplice e sicuramente ben sviluppato nell`industria moderna
 * Porta per� con se nuovi concetti chiave come la codifica dei codici wireless
 * con token univoci rendendo impossibile l`hackeraggio da parte di man in the middle

 * Verr� sviluppato poi in seguito anche un programma che gestir� tutta le animazioni
 * dello schermo Oled, mantenendo al minimo l`utilizzo di memoria (compressione, azioni prestabilite)

 * Successivamente verranno rilasciati anche i sorgenti dell`hardware
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Utilities/functions.h"
#include "Utilities/interrupts.h"
#include "Wireless/wThings.h"
#include "define.h"

extern int	foo;
volatile extern uint8_t	Sending;
volatile uint8_t UsartBufferData;
volatile uint8_t SendingUSART;

volatile extern uint8_t Ocrlast;
volatile extern _Bool   LedOn;
volatile extern _Bool   Reverse;
volatile extern _Bool   startLed;

volatile extern uint8_t lastPIND;

volatile extern uint8_t tempTimerLed;
volatile        times    Orario = {0};
volatile        times    OrarioInizioLed = {0};
volatile        times    OrarioFineLed = {0};



int main(void)
{
	// User Custom Program
  set_pin(SensorePorta, 5, INPUT,  0);
  set_pin(LedPWM,       6, OUTPUT, 0);
	// User Custom Program

  // Load Orario from EEPROM
  EEARH = 0x00; EEARL = 0x00;
  EECR = 0x00;
  EECR |= (1 << EERIE) | (1 << EERE);
  Orario.Secondi = EEDR;
  EEARH = 0x00; EEARL = 0x01;
  EECR |= (1 << EERE);
  Orario.Minuti = EEDR;
  EEARH = 0x00; EEARL = 0x02;
  EECR |= (1 << EERE);
  Orario.Ore = EEDR;
  EEARH = 0x00; EEARL = 0x03;
  EECR |= (1 << EERE);
  Orario.Giorno = EEDR;
  EEARH = 0x00; EEARL = 0x04;
  EECR |= (1 << EERE);
  Orario.Mesi = EEDR;
  EEARH = 0x00; EEARL = 0x05;
  EECR |= (1 << EEDR);
  EEARH = 0x00; EEARL = 0x00;
  // Load Orario from EEPROM

  sei(); // Enable Interrupts

	// PWM Led on PD6
  OCR0A = 0; // set PWM for 50% duty cycle
  TCCR0A |= (1 << COM0A1); // set none-inverting mode
  TCCR0A |= (1 << WGM01) | (1 << WGM00); // set fast PWM Mode
  TCCR0B |= (1 << CS01); // set prescaler to 8 and starts PWM
  // PWM Led on PD6

	// INTERRUPT Porta PCINT21
  //(*PORTA(0x68)) = 0b00000100;
	PCICR   |= (1 << PCIE2);
	PCMSK2  |= (1 << 5);
	// INTERRUPT PORTA
   lastPIND = PIND;

  foo = 1;
  tempTimerLed = 50; startLed = 1; // Accensione dei Led
  spiconfig sconfig = {SLAVE, MSBFIRST, DEFAULT, DEFAULT}; 
  start_SPI(sconfig);

  while (1)
  {
		// Do Something
  }
}
