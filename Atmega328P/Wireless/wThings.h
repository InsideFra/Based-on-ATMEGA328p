/*
 * wThings.h
 *
 * Created: 25/02/2018 00:22:54
 *  Author: franc
 */ 


#ifndef WTHINGS_H_
#define WTHINGS_H_

#include "../Utilities/functions.h"
#include <avr/io.h>
#include "../define.h"

void startWireless();
uint32_t* wRead_Register (uint8_t hexadress);
void      wWrite_Register(uint8_t hexadress, uint32_t *datatowrite);
void      wNOP();


#endif /* WTHINGS_H_ */