#ifndef _DS3231DRIVER_H_
#define _DS3231DRIVER_H
#include <RTClib.h>
#include <ESP32Ping.h>

const char* remote_host = "www.google.com";
RTC_DS3231 rtc;
char  TimeAndDate[16];


/**
 * @brief	Khoi tao module thoi gian thuc
 *
 * @return  None
 */
void DS3231_Init();



/**
 * @brief	luu tru thoi gian thuc vao bien TimeAndDate
 *
 * @return  None
 */
void DS3231_GetData();
#endif
