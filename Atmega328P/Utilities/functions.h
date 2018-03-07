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

void set_pin(int PORT, int PINNumb, _Bool INPOUT, _Bool INOUT);
void toggle_pin(int PORT, int PINNumb);

// SPI
void start_SPI(int PORTMosi, int PORTMiso, int PORTSckl, _Bool MasterSlave, _Bool MSBLSBFirst, int clk, _Bool clkRisingFalling);
void sendoverspi(char* data);
// End SPI

// Timers
void updateRTC();
// Timers

struct time functTime();



#endif /* FUNCTIONS_H_ */