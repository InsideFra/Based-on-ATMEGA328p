/*
 * drivers.h
 *
 * Created: 25/09/2018 21:58:16
 *  Author: franc
 */


#ifndef DRIVERS_H_
#define DRIVERS_H_

void LoadDriverInMemory();
void DiscardDriverFromMemory();

enum SensorDefinition {
  SensorType;
  ReadTemp;
}

enum SensorDescription {
  SensorID;
  SensorType;
  SensorNumber;
  checkTemperature;
};

enum SensorDescription DS18B20 = {0, 0, 0, TemperaturaDS18B20()};


enum SensorList {
  SensorDescription;
};

enum SensorList sensorlist[10] = {DS18B20, {0}};

SensorList = {

}

uint8_t ReadTemp(uint8_t SensorID);
uint8_t TemperaturaDS18B20();







#endif /* DRIVERS_H_ */
