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

void* pointFunzTimer[6];

void  set_pin(int PORT, int PINNumb, _Bool INPOUT, _Bool LowHIGH);
void  toggle_pin(int PORT, int PINNumb);
_Bool getstatus_pin(int PORT, int PINNUmb);

// SPI
typedef struct SPIConfigs {
  _Bool MasterSlave;
  _Bool MSBLSBFirst;
  uint8_t clk;
  _Bool clkRisingFalling;
} spiconfig;
void  start_SPI(spiconfig SPIC);
_Bool sendoverspi(uint8_t _data, uint8_t action);
// End SPI

// i2c

// End i2c

// USART
volatile uint8_t UsartBufferData;
volatile uint8_t SendingUSART;
typedef struct USARTConfig {
  uint8_t Baudrate;
  uint8_t FrameFormat;
  uint8_t TransmitterReceiver;
} usartdata;
void startUSART(usartdata __usartconfig);
void sendoverUSART(uint8_t __message);
// USART

// Timers
void updateRTC();
void updateEEPROM();

void setNewTimer(uint16_t MS, _Bool Repeat, void* pointFunzione);
void deleteTimer(uint8_t TimerNumber);
//  End Timers

void write_Register8(uint8_t Register, char Value);
uint8_t read_Register8(uint8_t HexAddress);

void defineTimer(uint8_t TimerNumber, uint8_t Mode, uint8_t prescaler);
void setTimerComp(uint8_t TimerNumber, _Bool ComparatorN, uint8_t ComparatorValue);
void setTimerFunction(uint8_t TimerNumber, _Bool ComparatorN, void* PointerFunction);
void delTimerFunction(uint8_t TimerNumber, _Bool ComparatorN);

void setPWM(void* Funzione);
void setFakePWM(void* Funzione);

void EEPROM_write(uint8_t uiAddress, uint8_t data);

#endif /* FUNCTIONS_H_ */
