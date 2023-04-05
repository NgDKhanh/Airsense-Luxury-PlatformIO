/*******************************************************************
 **    O3ppbDislplay(int)  O3ppmDisplay(float)  O3ugDisplay(int)  **    
 **    min_o3_ppb(int)  min_o3_ppm(float)  min_o3_ug(int)         **
 **    max_o3_ppb(int)  max_o3_ppm(float)  max_o3_ug(int)         **
 **    TemDisplay(char)            WifiState                      **
 **    HumDisplay(char)            SDState                        **
 **    TemDisplay_F(uint16_t)         Rx: pin 33                  **
 **    pm25Display(int)                Tx: pin 25                 **
 **    pm10Display(int)                                           **
 **    TimeAndDate(string)                                        **
 *******************************************************************/

/* Khai bao thu vien man hinh TFT */
#ifndef _NEXTIONDRIVER_H
#define _NEXTIONDRIVER_H
#include <iostream>
#include "EasyNextionLibrary.h"
#include <EEPROM.h>

EasyNex myNex(Serial2);




/**
 * @brief	Khoi tao man hinh
 *
 * @return  None
 */
void Screen_Init();

/**
 * @brief	Doc du lieu tu man hinh va luu vao
 *        cac bien toan cuc trong config.h
 * 
 * @return  None
 */
void Screen_GetDisplayData();

/**
 * @brief	Luu tru cac gia tri da calibcalib tu man hinh vao the nho
 *
 * @return  None
 */
void Screen_SaveCalibData2SDcard();


/**
 * @brief	Doc cac gia tri calib tu the nho len man hinh
 *
 * @return  None
 */
void Screen_DisplayCalibData();
/**
 * @brief	ghi cac gia tri len man hinh
 *
 * @return  None
 */
void Screen_DisplayData();
#endif