#ifndef _SHT85DRIVER_H
#define _SHT85DRIVER_H

#include "SHTSensor.h"

SHTSensor sht(SHTSensor::SHT3X);

extern uint     lastReadSHT;
extern float 	TemDisplay;
extern float 	TemDisplay_F;
extern float 	HumDisplay;


/**
 * @brief	Doc gia tri cua SHT
 *
 * @return  None
 */
void SHT_GetData();

/**
 * @brief	Khoi tao SHT
 *
 * @return  None
 */
void SHT_Init();
#endif
