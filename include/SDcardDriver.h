#ifndef _SDCARDDRIVER_H_
#define _SDCARDDRIVER_H_
#include <FS.h>

File myFile;
File myFile2;
File myFile3;
File myFile4;
const int chipSelect = 5;

extern char char_array[30];
extern char fileNameCalib[];


extern char nameFileCalib1[16];
extern char nameFileCalib[16];

/**
 * @brief	ham de khoi tao the nho
 *
 * @return  None
 */
void SDcard_Init();


/**
 * @brief	split gia tri du lieu tu the nho
 *
 * @return  None
 */
void Screen_SplitStringData();

/**
 * @brief	Doc file tu trong the nho
 *
 * @return  None
 */
void SDcard_ReadFile();

/**
 * @brief	ham de luu gia tri vao the nho
 * @param	hum - gia tri do am
 * @param	tem - gia tri nhiet do
 * @param	pm1 - pm1.0
 * @param	pm25 - pm2.5
 * @param	pm10 - pm10
 * @param	O3ppb - 03
 * @param	O3ppm - 03
 * @param	O3ug - 03
 * @param	minpm25 - muc min cua pm25
 * @param	maxpm25 - muc max cua pm25
 * @return  None
 */
void SDcard_SaveDataFile(float hum,float tem,int pm1,int pm25,int pm10,int O3ppb,float O3ppm,float O3ug ,int minpm25, int maxpm25);

/**
 * @brief	Chuong trinh hoat dong cua the nho
 *
 * @return  None
 */
void runProgramWithSD();
#endif
