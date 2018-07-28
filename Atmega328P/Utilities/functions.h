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

void set_pin(int PORT, int PINNumb, _Bool INPOUT, _Bool LowHIGH);
void toggle_pin(int PORT, int PINNumb);
_Bool getstatus_pin(int PORT, int PINNUmb);

// SPI
void start_SPI(int PORTMosi, int PORTMiso, int PORTSckl, _Bool MasterSlave, _Bool MSBLSBFirst, int clk, _Bool clkRisingFalling);
_Bool sendoverspi(uint8_t _data, uint8_t action);
// End SPI

// i2c

// End i2c

// Timers
void updateRTC();

void setNewTimer(uint16_t MS, _Bool Repeat, void* pointFunzione);
void deleteTimer(uint8_t TimerNumber);
//  End Timers

struct time functTime();

void write_Register8(uint8_t Register, char Value);
uint8_t read_Register8();



#endif /* FUNCTIONS_H_ */
