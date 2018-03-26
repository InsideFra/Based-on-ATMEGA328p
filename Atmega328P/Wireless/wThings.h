/*
 * wThings.h
 *
 * Created: 25/02/2018 00:22:54
 *  Author: franc
 */ 


#ifndef WTHINGS_H_
#define WTHINGS_H_

#include <avr/io.h>

void      startWireless();
uint8_t   wRead_Register8   (uint8_t hexadress);
uint32_t  wRead_Register32  (uint8_t hexadress);
void      wWrite_Register8  (uint8_t hexadress, uint8_t datatowrite);
void      wWrite_Register32 (uint8_t hexadress, uint32_t datatowrite, uint8_t buflengh);
void      wNOP();


#endif /* WTHINGS_H_ */