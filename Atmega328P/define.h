/*
 * define.h
 *
 * Created: 04/03/2018 15:14:58
 *  Author: franc
 */


#ifndef DEFINE_H_
#define DEFINE_H_

#define F_CPU 16000000

#define PORTA (volatile uint8_t*)

#define PMiso 0x25 // pin 4
#define PMosi 0x25 // pin 3
#define PSckl 0x25 // pin 5
#define PORTSS 0x25 // pin 2


#define ButtonUP  0x2B// pin 5
#define ButtonDOWN 0x2B // pin 6
#define Speacker 0x2B // pin 7

// Wireless
#define WCSN 0x25 // pin 0
#define WIRQ 0x25 // pin 1
#define WCE  0x25 // pin 2
// Wireless

// PWM
#define LedPWM 0x2B // PORTD pin 6
// PWM

// Input PORTA
#define SensorePorta 0x2B // PORTD pin 5
// Input Porta

#define INPUT 0
#define OUTPUT 1

#define wRegister 0b11010010

#define MAXTIMERS 10

struct time {
	uint8_t Secondi;
	uint8_t Minuti;
	uint8_t Ore;
	uint8_t Giorno;
	uint8_t Mesi;
	uint8_t Anno; // Since 1999 to 2135
};

#endif /* DEFINE_H_ */
