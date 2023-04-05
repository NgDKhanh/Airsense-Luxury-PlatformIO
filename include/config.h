#pragma once
#include <NTPClient.h>
#include <WiFiUdp.h>

//========================== DEFINE CHO TOAN BO CODE ========================
#define DEBUG_SERIAL        1
#define USING_SD_CARD       1
#define USING_MQTT          0

#define O3_SENSOR           0      
#define O3_SENSOR_DF_ROBOT  0
#define O3_SENSOR_MQ131     0
#define TFLP01_USED         1
#define SHT85_USED          1
#define DS3231_USED         1

//========================== DEFINE CHO MAN HINH ========================
#define SERIAL_DEBUG_BAUDRATE 9600
#define ERROR_READ_DISPLAY 777777

//========================== DEFINE CHO MAN HINH ========================

#define PIN_TX_TFLP01   17
#define PIN_RX_TFLP01   16

//========================== DEFINE CHO MAN HINH ========================

#define PIN_TX_TFT      33
#define PIN_RX_TFT      25

//========================== DEFINE CHO MAN HINH ========================

#define PIN_NUM_MISO    21
#define PIN_NUM_MOSI    19
#define PIN_NUM_CLK     18
#define PIN_CS_SD_CARD  5
//========================== DEFINE CHO MAN HINH ========================

#define PIN_SDA_GPIO    26
#define PIN_SCL_GPIO    27
#define I2C_CLOCK_SPEED 100000ul
//========================== DEFINE CHO MAN HINH ========================

#define PIN_NEO_PIXEL   23
//========================== DEFINE CHO MAN HINH ========================

#define PIN_BUTTON_1    35
#define PIN_BUTTON_2    34
#define outputA         33
#define outputB         25
#define switch          32
//========================== DEFINE CHO MAN HINH ========================

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "de.pool.ntp.org", 3600*7, 60000);

//========================== DEFINE CHO MAN HINH ========================

extern uint lastreconnectwifi;
extern uint lastPressButton;
extern uint lastsenddatatoSD_MQTT;

//============= KHAI BAO CAC BIEN HIEN THI TREN MAN HINH ================

extern char  WifiState;
extern char  SDState;

char  tempStringDisplay[10];

extern float temp;
extern float humi;
extern int   yearCalib;
extern int   O3ppbDislplay;
extern float O3ppmDisplay;
extern float O3ugDisplay;
extern int   min_o3_ppb;
extern float min_o3_ppm;
extern float min_o3_ug;
extern int   max_o3_ppb;
extern float max_o3_ppm;
extern float max_o3_ug;

/*
float temp		 = 20.5;
float humi		 = 60;
int   yearCalib  = 2021;
int   O3ppbDislplay = 0;
float O3ppmDisplay = 0;
float O3ugDisplay  = 0;
int   min_o3_ppb = 100;
float min_o3_ppm = 100;
float min_o3_ug  = 100;
int   max_o3_ppb = 0;
float max_o3_ppm = 0;
float max_o3_ug  = 0;
*/

//========================== khai bao de dung cho the nho ========================

bool  	stateSDcard	 = 0;
uint8_t MacAddress1[6];
char 	nameDevice1[12];

//========================== cac bien de calib gia tri ========================

extern int dataCalibInt;
extern int tempCalibInt;
extern int humiCalibInt;
extern int pm1CalibInt;
extern int pm10CalibInt;
extern int pm25CalibInt;
extern int tempCalibFloat;
extern int humiCalibFloat;
int getTemp = 0;

//========================== cac bien de doc gia tri calib tu man hinh ========================

extern float tempFromDisplay_a;
extern float tempFromDisplay_b;
extern float humiFromDisplay_a;
extern float humiFromDisplay_b;
extern float pm1FromDisplay_a;
extern float pm1FromDisplay_b;
extern float pm10FromDisplay_a;
extern float pm10FromDisplay_b;
extern float pm25FromDisplay_a;
extern float pm25FromDisplay_b;
extern float o3FromDisplay_a;
extern float o3FromDisplay_b;


/**
 * @brief When read calib value from Nextion display, we have a string with a format like
 * "abcde" or "a-bcd". eg: "2-1234": 2 is power and -1234 is value, so the real value we 
 * receive is (-1234) / (10^2) = -12.34
 * 
 * @param textFromDisplay : string we read from Nextion display
 * @return if read from display successful: the float value that we really receive \
 *         else: ERROR_READ_DISPLAY
 */
float textFromDisplay2Float(String textFromDisplay){
    if(textFromDisplay == "ERROR") {
        return ERROR_READ_DISPLAY;
    }
    int power = textFromDisplay.substring(0, 1).toInt();
    int value = textFromDisplay.substring(1).toInt();
    return (float)(value / pow(10, power));
}


