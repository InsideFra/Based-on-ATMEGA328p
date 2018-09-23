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

void      setRX();
void      setTX();
void      setAirRate(uint8_t rate);
void      setChannel(uint8_t channel);
void      setPA(uint8_t PA);


_Bool	  wSendPackage(uint8_t data);
_Bool	  wPackageAvailable();
void	  wReadPackage(uint8_t* buffer);


#endif /* WTHINGS_H_ */
