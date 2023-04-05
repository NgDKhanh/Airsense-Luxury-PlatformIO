#include "DS3231Driver.h"
#include "config.h"
#include "RTClib.h"
#include <ESP32Ping.h>


void DS3231_Init()
{
  rtc.begin();
  if (WiFi.status() == WL_CONNECTED){
    if (Ping.ping(remote_host)){
      timeClient.update();
      uint epochTime = timeClient.getEpochTime();
      rtc.adjust(DateTime(epochTime));
      Serial.println("updatetimeDS3231");
    }
  }
    DateTime now = rtc.now();
#ifdef	DEBUG_SERIAL
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
#endif
}


void DS3231_GetData()
{
    DateTime now = rtc.now();
    if(now.hour()<10 && now.minute()<10){
      sprintf(TimeAndDate,"0%d:0%d  %d/%d/%d",int(now.hour()),int(now.minute()),int(now.day()),int(now.month()),int(now.year()%2000));
    }
    if(now.hour()>=10 && now.minute()<10){
      sprintf(TimeAndDate,"%d:0%d  %d/%d/%d",int(now.hour()),int(now.minute()),int(now.day()),int(now.month()),int(now.year()%2000));
    } 
    if(now.hour()<10 && now.minute()>=10){
      sprintf(TimeAndDate,"0%d:%d  %d/%d/%d",int(now.hour()),int(now.minute()),int(now.day()),int(now.month()),int(now.year()%2000));
    } 
    if(now.hour()>=10 && now.minute()>=10){
      sprintf(TimeAndDate,"%d:%d  %d/%d/%d",int(now.hour()),int(now.minute()),int(now.day()),int(now.month()),int(now.year()%2000));
    } 
    
#ifdef  DEBUG_SERIAL
      Serial.println(TimeAndDate);
#endif
}
