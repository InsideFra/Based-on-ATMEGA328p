/*
 * functions.h
 *
 * Created: 04/03/2018 11:54:27
 *  Author: franc
 */ 

#include <avr/io.h>

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

int foo;

// RTC

void set_pin(int PORT, int PINNumb, _Bool INPOUT, _Bool LowHIGH);
void toggle_pin(int PORT, int PINNumb);
_Bool getstatus_pin(int PORT, int PINNUmb);

// SPI
void start_SPI(int PORTMosi, int PORTMiso, int PORTSckl, _Bool MasterSlave, _Bool MSBLSBFirst, int clk, _Bool clkRisingFalling);
_Bool sendoverspi(uint8_t _data, uint8_t action);
// End SPI

// Timers
void updateRTC();
// Timers

struct time functTime();



#endif /* FUNCTIONS_H_ */