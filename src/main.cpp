//========================== Khai bao thu vien ========================

#include <Arduino.h>
#include <string>
#include "Wire.h"
#include <SPI.h>
#include "WiFi.h"
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

bool isLongPressButton();
char WifiState;

float temp		 = 20.5;
float humi		 = 60;
int   yearCalib  = 2023;
int   O3ppbDislplay = 0;
float O3ppmDisplay = 0;
float O3ugDisplay  = 0;

uint lastreconnectwifi = 0;
uint lastPressButton = 0;
uint lastsenddatatoSD_MQTT = millis();


//========================== Khai bao cac file code ========================

#include "config.h"


#include "DS3231Driver.h"
#include "MQTTConnection.h"
#include "SDcardDriver.h"
#include "SHT85Driver.h"
#include "MQ131Driver.h"
#include "NextionDriver.h"
#include "TFLP01Driver.h"


//==========================     SETUP       ========================

void setup() {
  myNex.NextionListen();
  Serial.begin(SERIAL_DEBUG_BAUDRATE);
  Serial2.begin(SERIAL_DEBUG_BAUDRATE);
  // pinMode(PIN_BUTTON_1,	INPUT);
  // Wire.begin(PIN_SDA_GPIO, PIN_SCL_GPIO, I2C_CLOCK_SPEED);
  // WiFi.begin();
  // WiFi.macAddress(MacAddress1);
  
#if USING_MQTT
  MQTT_InitClient(topic, espID, mqttClient);
  timeClient.begin();
#endif
  // khoi tao cac cam bien
#if O3_SENSOR
  Serial.println("Check Ozone Sensor");
  O3_init();
  delay(10);
#endif
/*
#if TFLP01
  Serial.println("Check Dusty  Sensor");
  TFLP01_Init();
  delay(10);
#endif
  
#if SHT85_USED
  Serial.println("Check Temperature and Humidity Sensor");
  SHT_Init();
  delay(10);
#endif
  
#if DS3231
  Serial.println("Check RTC Module");
  DS3231_Init();
  delay(10);
#endif
*/

#if USING_SD_CARD
  Serial.println("Check SD");
  SDcard_Init();
  delay(10);
  Serial.println("Check Screen");
#endif

  Screen_Init();
  Serial.println("Init screen successful!");

#if USING_SD_CARD
//   luu file text theo nam
  sprintf(nameFileCalib,"/calib-%d.txt",yearCalib);
#endif
}

//==========================     LOOP       ========================

void loop() {
    
	// check button de smartConfig
    if (isLongPressButton())
    {
      uint8_t a=0;
      while (!WiFi.smartConfigDone() && a<120) {
        Serial.println(".");
        WifiState = 2;
        myNex.writeNum("dl.wifi.val",WifiState);
        a++;
      }
    }
	// check neu wifi da ket noi thi cho bien wifi man hinh bat len
    if (WiFi.status() == WL_CONNECTED){
       WifiState = 1;
    }
    else
	{
		// hien thi chua ket noi wifi
      WifiState = 0;
      if((millis()-lastreconnectwifi>60000) || (millis()<lastreconnectwifi)){
        lastreconnectwifi = millis();
      }
    }
	// get data
    SHT_GetData();
    TFLP01_GetData();
    DS3231_GetData();
#if O3_SENSOR
    O3_GetData();
#endif
    Screen_DisplayData();
    Serial.println("\n\n\n------------Screen_DisplayData-------------\n\n\n");
    Screen_GetDisplayData();
    Serial.println("\n\n\n------------Screen_GetDisplayData-----------\n\n\n");


    


	//gui du lieu len mqtt va luu tru trong the nho
    if((millis()-lastsenddatatoSD_MQTT> 10000) || (millis()<lastsenddatatoSD_MQTT))
    {
#ifdef USING_SD_CARD
//		// luu vao trong the nho
      SDcard_SaveDataFile(HumDisplay,TemDisplay,pm1Display,pm25Display,pm10Display,O3ppmDisplay,O3ppmDisplay,O3ugDisplay,min_pm25,max_pm25);
      runProgramWithSD();
#endif
#if USING_MQTT
      MQTT_PostData(HumDisplay,TemDisplay,pm1Display,pm25Display,pm10Display,O3ppmDisplay);
#endif
      lastsenddatatoSD_MQTT = millis();
    }
#if USING_MQTT
    mqttClient.loop();
#endif
}



bool isLongPressButton()
{
  if (millis() - lastPressButton > 4000 && digitalRead(PIN_BUTTON_1) == 0)
  {
    return true;
  }
  else if (digitalRead(PIN_BUTTON_1) == 1)
  {
    lastPressButton = millis();
  }
  return false;
}
