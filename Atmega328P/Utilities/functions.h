/*
 * functions.h
 *
 * Created: 04/03/2018 11:54:27
 *  Author: franc
 */ 

#include <avr/io.h>

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

void set_pin(int PORT, int PINNumb, _Bool INPOUT, _Bool INOUT);
void toggle_pin(int PORT, int PINNumb);



#endif /* FUNCTIONS_H_ */