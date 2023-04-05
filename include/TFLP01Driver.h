#ifndef _TFLP01DRIVER_H_
#define _TFLP01DRIVER_H_


unsigned int TFLP01_pm10sum 	= 0;
unsigned int TFLP01_pm25sum 	= 0;
unsigned int TFLP01_pm1sum 		= 0;
int	 dataTFLP01count 	= 0;
bool 	 TFLP01_read 		= false;
int 	 pm1Display			= 0;
int 	 pm25Display			= 0;
int 	 pm10Display			= 0;
int 	 max_pm25			= 0;
int 	 min_pm25			= 1000;

/**
 * @brief  Return CRC trong data response của TF-LP-01
 *
 * @return  None
 */
unsigned int crc16_modbus(char *modbusdata , unsigned int Length);

/**
 * @brief Setup TF-LP-01
 *
 * @return  None
 */
void TFLP01_Init();

/**
 * @brief Doc du lieu tu cam bien bui
 *
 * @return  None
 */
void TFLP01_GetData();
#endif