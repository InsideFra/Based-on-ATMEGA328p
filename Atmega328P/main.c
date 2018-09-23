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
volatile extern uint8_t UsartBufferData;
volatile extern uint8_t SendingUSART;

volatile extern uint8_t Ocrlast;
volatile extern _Bool   LedOn;
volatile extern _Bool   Reverse;
volatile extern _Bool   startLed;

extern volatile uint8_t lastPIND;


int main(void)
{
  // USART
  SendingUSART = 0;
	UsartBufferData = 0;
	// USART

	set_pin(SensorePorta, 5, INPUT,  0);
	set_pin(LedPWM,       6, OUTPUT, 0);

	// Enable Interrupts and configs
	//(*(volatile uint8_t*) (0x5F)) |= (1 << 7); // Enable interrupts
	sei();

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

	// enable Wireless
    /* startWireless();
		*	 Meglio focalizzarsi prima sui Timer e funzioni basi
		*  Successivamente Wireless & Wifi */
	// END

	//start_SPI(spiconfig Spic = {0, 0, 0, 0});
	foo = 1;
    while (1)
    {
				// Do Something
    }
}
