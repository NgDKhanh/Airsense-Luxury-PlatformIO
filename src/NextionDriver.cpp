#include "NextionDriver.h"
#include "config.h"
#include "SDcardDriver.h"
#include "DS3231Driver.h"
#include "SHT85Driver.h"
#include "TFLP01Driver.h"
#include <string>
#include "string.h"
#include <sstream>
#include <SD.h>


int dataCalibInt     = 0;
int tempCalibInt     = 0;
int humiCalibInt     = 0;
int pm1CalibInt      = 0;
int pm10CalibInt     = 0;
int pm25CalibInt     = 0;
int tempCalibFloat   = 0;
int humiCalibFloat   = 0;

float tempFromDisplay_a 	= 1;
float tempFromDisplay_b 	= 0;
float humiFromDisplay_a 	= 1;
float humiFromDisplay_b 	= 0;
float pm1FromDisplay_a	  = 1;
float pm1FromDisplay_b    = 0;
float pm10FromDisplay_a 	= 1;
float pm10FromDisplay_b 	= 0;
float pm25FromDisplay_a 	= 1;
float pm25FromDisplay_b 	= 0;
float o3FromDisplay_a     = 1;
float o3FromDisplay_b     = 0;

char nameFileCalib[16];


void Screen_Init(){
    myNex.begin(SERIAL_DEBUG_BAUDRATE);
    EEPROM.begin(512);
}


void Screen_GetDisplayData()
{
    // cac bien de luu cac gia tri calib gan nhat
    float last_a_temp = 1;
    float last_b_temp = 0;
    float last_a_humi = 1;
    float last_b_humi = 0;  
    float last_a_pm1 = 1;
    float last_b_pm1 = 0;
    float last_a_pm10 = 1;
    float last_b_pm10 = 0;
    float last_a_pm25 = 1;
    float last_b_pm25 = 0;
    
    

    // cac bien doc gia tri calib tu man hinh page calib 
    float calib_a_temp_val  = textFromDisplay2Float(myNex.readStr("calib.a_temp.txt")); 
    float calib_b_temp_val  = textFromDisplay2Float(myNex.readStr("calib.b_temp.txt"));
    float calib_a_humi_val  = textFromDisplay2Float(myNex.readStr("calib.a_humi.txt"));   
    float calib_b_humi_val  = textFromDisplay2Float(myNex.readStr("calib.b_humi.txt"));  
    float calib_a_o3_val    = textFromDisplay2Float(myNex.readStr("calib.a_o3.txt"));
    float calib_b_o3_val    = textFromDisplay2Float(myNex.readStr("calib.b_o3.txt"));
    float calib_a_pm1_val   = textFromDisplay2Float(myNex.readStr("calib.a_pm1.txt"));
    float calib_b_pm1_val   = textFromDisplay2Float(myNex.readStr("calib.b_pm1.txt"));
    float calib_a_pm25_val  = textFromDisplay2Float(myNex.readStr("calib.a_pm25.txt"));
    float calib_b_pm25_val  = textFromDisplay2Float(myNex.readStr("calib.b_pm25.txt"));
    float calib_a_pm10_val  = textFromDisplay2Float(myNex.readStr("calib.a_pm10.txt"));
    float calib_b_pm10_val  = textFromDisplay2Float(myNex.readStr("calib.b_pm10.txt"));
    float calib_a_co2_val   = textFromDisplay2Float(myNex.readStr("calib.a_co2.txt"));
    float calib_b_co2_val   = textFromDisplay2Float(myNex.readStr("calib.b_co2.txt"));

    // kiem tra loi
    if(calib_a_temp_val != ERROR_READ_DISPLAY){                     
      last_a_temp = calib_a_temp_val;  
      if(last_a_temp != 0)                                     
      {
         tempFromDisplay_a = last_a_temp;
      }
    }                           
    else if(calib_a_temp_val == ERROR_READ_DISPLAY){
      calib_a_temp_val = last_a_temp;
    }

    // Read data temp Float
    if(calib_b_temp_val != ERROR_READ_DISPLAY){                     
      last_b_temp = calib_b_temp_val;  
      if(last_b_temp !=0)                                     
      {
         tempFromDisplay_b = last_b_temp;
      }
    }                                       
    else if(calib_b_temp_val == ERROR_READ_DISPLAY){
      calib_b_temp_val = last_b_temp;
    }

    // read data calib humidity
    if(calib_a_humi_val != ERROR_READ_DISPLAY){                     
      last_a_humi = calib_a_humi_val;  
      if(last_a_humi != 0)                                     
      {
         humiFromDisplay_a = last_a_humi;
      }
    }                                     
    else if(calib_a_humi_val == ERROR_READ_DISPLAY){
      calib_a_humi_val = last_a_humi;
    }

    // Read data calib humidity
    if(calib_b_humi_val != ERROR_READ_DISPLAY){                     
      last_b_humi = calib_b_humi_val;  
      if(last_b_humi !=0)                                     
      {
         humiFromDisplay_b = last_b_humi;
      }
    }                                       
    else if(calib_b_humi_val == ERROR_READ_DISPLAY){
      calib_b_humi_val = last_b_humi;
    }

    // read data calib pm1
    if(calib_a_pm1_val != ERROR_READ_DISPLAY){                     
      last_a_pm1 = calib_a_pm1_val;  
      if(last_a_pm1 != 0)                                     
      {
         pm1FromDisplay_a = last_a_pm1;
      }
    }                                       
    else if(calib_a_pm1_val == ERROR_READ_DISPLAY){
      calib_a_pm1_val = last_a_pm1;
    }

    // read data calib pm1
    if(calib_b_pm1_val != ERROR_READ_DISPLAY){                     
      last_b_pm1 = calib_b_pm1_val;  
      if(last_b_pm1 != 0)                                     
      {
         pm1FromDisplay_b = last_b_pm1;
      }
    }                                       
    else if(calib_a_pm1_val == ERROR_READ_DISPLAY){
      calib_b_pm1_val = last_b_pm1;
    }

    // Read data calib pm10
    if(calib_a_pm10_val != ERROR_READ_DISPLAY){                     
      last_a_pm10 = calib_a_pm10_val;  
      if(last_a_pm10 !=0)                                     
      {
         pm10FromDisplay_a = last_a_pm10;
      }
    }                                      
    else if(calib_a_pm10_val == ERROR_READ_DISPLAY){
      calib_a_pm10_val = last_a_pm10;
    }

    // Read data calib pm10
    if(calib_b_pm10_val != ERROR_READ_DISPLAY){                     
      last_b_pm10 = calib_b_pm10_val;  
      if(last_b_pm10 !=0)                                     
      {
         pm10FromDisplay_b = last_b_pm10;
      }
    }                                      
    else if(calib_b_pm10_val == ERROR_READ_DISPLAY){
      calib_b_pm10_val = last_b_pm10;
    }

    // Read data calib pm2.5
    if(calib_a_pm25_val != ERROR_READ_DISPLAY){                     
      last_a_pm25 = calib_a_pm25_val;  
      if(last_a_pm25 !=0)                                     
      {
         pm25FromDisplay_a = last_a_pm25;
      }
    }                                       
    else if(calib_a_pm25_val == ERROR_READ_DISPLAY){
      calib_a_pm25_val = last_a_pm25;
    }

    // Read data calib pm2.5
    if(calib_b_pm25_val != ERROR_READ_DISPLAY){                     
      last_b_pm25 = calib_b_pm25_val;  
      if(last_b_pm25 !=0)                                     
      {
         pm25FromDisplay_b = last_b_pm25;
      }
    }                                       
    else if(calib_a_pm25_val == ERROR_READ_DISPLAY){
      calib_b_pm25_val = last_b_pm25;
    }
    

#ifdef DEBUG_SERIAL
    Serial.println(tempFromDisplay_a); 
    Serial.println(tempFromDisplay_b);
    Serial.println(humiFromDisplay_a);
    Serial.println(humiFromDisplay_b);
    Serial.println(pm1FromDisplay_a);
    Serial.println(pm1FromDisplay_b);
    Serial.println(pm10FromDisplay_a);
    Serial.println(pm10FromDisplay_b);
    Serial.println(pm25FromDisplay_a);  
    Serial.println(pm25FromDisplay_b);
    Serial.println("----------------");
#endif
}


void Screen_SaveCalibData2SDcard()
{
      if( tempFromDisplay_a < -100 || tempFromDisplay_a >1000 || humiFromDisplay_a < -100 || humiFromDisplay_a >1000 || pm1FromDisplay_a < -100 || pm1FromDisplay_a >1000 || pm10FromDisplay_a < -100  || pm10FromDisplay_a >1000 || pm25FromDisplay_a < -100 || pm25FromDisplay_a >1000)
      {
#ifdef DEBUG_SERIAL
        Serial.println("-----*** Dont write to SD card ***----");
#endif
      }
      else
      {
          myFile = SD.open(nameFileCalib,FILE_WRITE);
          if(myFile)
          {
            char mess[256] = {0};
            sprintf(mess,"%d|%d|%d|%d|%d|%d|%d|",tempFromDisplay_a, humiFromDisplay_a, pm1FromDisplay_a, pm10FromDisplay_a, pm25FromDisplay_a);
#ifdef DEBUG_SERIAL
            Serial.print("mess:");
            Serial.println(mess);
#endif
            SDState = 1;
            myFile.println(mess);        
            myFile.close();
          }
            else
          { 
            Serial.println("reconnect SD");
            if(!SD.begin(PIN_CS_SD_CARD, SPI)) 
                SDState = 0; 
            else 
                SDState = 1; 
        }
      }
      
}



void Screen_DisplayCalibData(){
  myNex.writeNum("dl.n9.val", dataCalibInt); //
  myNex.writeNum("dl.n4.val", tempCalibInt);
  myNex.writeNum("dl.n5.val", humiCalibInt);
  myNex.writeNum("dl.n6.val", pm1CalibInt);
  myNex.writeNum("dl.n7.val", pm10CalibInt);
  myNex.writeNum("dl.n8.val", pm25CalibInt);
  myNex.writeNum("dl.n7.val", tempCalibFloat);
  myNex.writeNum("dl.n8.val", humiCalibFloat);
}


void Screen_DisplayData(){
  myNex.writeNum("dl.wifi.val", WifiState);
  myNex.writeNum("dl.sd.val", SDState);
  
  myNex.writeStr("dl.time.txt", TimeAndDate);

  sprintf(tempStringDisplay,"%.1f", TemDisplay*tempFromDisplay_a + tempFromDisplay_b);
  myNex.writeStr("dl.temc.txt", tempStringDisplay);
  
  sprintf(tempStringDisplay,"%.1f", HumDisplay*humiFromDisplay_a + humiFromDisplay_b);
  myNex.writeStr("dl.hum.txt", tempStringDisplay);
  
  sprintf(tempStringDisplay,"%.1f", TemDisplay_F*tempFromDisplay_a + tempFromDisplay_b);
  myNex.writeStr("dl.temf.txt", tempStringDisplay);
  
  myNex.writeNum("dl.nppb.val", O3ppbDislplay);
  sprintf(tempStringDisplay,"%d", O3ppbDislplay);
  myNex.writeStr("dl.sppb.txt", tempStringDisplay);
  
  sprintf(tempStringDisplay,"%.1f",O3ugDisplay);
  myNex.writeStr("dl.sug.txt", tempStringDisplay);

  if(O3ppbDislplay < 10){
    sprintf(tempStringDisplay,"0.00%d", O3ppbDislplay);
  }
  else if(10 <= O3ppbDislplay && O3ppbDislplay < 100){
    sprintf(tempStringDisplay,"0.0%d", O3ppbDislplay);
  }
  else if(100 <= O3ppbDislplay && O3ppbDislplay < 1000){
    sprintf(tempStringDisplay, "0.%d", O3ppbDislplay);
  }
  else if(1000 <= O3ppbDislplay){
    sprintf(tempStringDisplay, "%d.%d", int(O3ppbDislplay/1000), int(O3ppbDislplay%1000));
  }
  myNex.writeStr("dl.sppm.txt", tempStringDisplay);

  sprintf(tempStringDisplay,"%d", min_o3_ppb);
  myNex.writeStr("dl.sminppb.txt", tempStringDisplay);
  
  sprintf(tempStringDisplay, "%.1f", min_o3_ug);
  myNex.writeStr("dl.sminug.txt", tempStringDisplay);

  if(min_o3_ppb < 10){
    sprintf(tempStringDisplay, "0.00%d", min_o3_ppb);
  }
  else if(10 <= min_o3_ppb && min_o3_ppb < 100){
    sprintf(tempStringDisplay, "0.0%d", min_o3_ppb);
  }
  else if(100 <= min_o3_ppb && min_o3_ppb < 1000){
    sprintf(tempStringDisplay, "0.%d", min_o3_ppb);
  }
  else if(1000 <= min_o3_ppb){
    sprintf(tempStringDisplay, "%d.%d", int(min_o3_ppb/1000), int(min_o3_ppb%1000));
  }

  myNex.writeStr("dl.sminppm.txt", tempStringDisplay);
  
  sprintf(tempStringDisplay,"%d", max_o3_ppb);
  myNex.writeStr("dl.smaxppb.txt", tempStringDisplay);
  
  sprintf(tempStringDisplay,"%.1f", max_o3_ug);
  myNex.writeStr("dl.smaxug.txt", tempStringDisplay);
  
  if(max_o3_ppb < 10){
    sprintf(tempStringDisplay, "0.00%d", max_o3_ppb);
  }
  else if(10 <= max_o3_ppb && max_o3_ppb < 100){
    sprintf(tempStringDisplay,"0.0%d", max_o3_ppb);
  }
  else if(100 <= max_o3_ppb && max_o3_ppb < 1000){
    sprintf(tempStringDisplay, "0.%d", max_o3_ppb);
  }
  else if(1000 <= max_o3_ppb){
    sprintf(tempStringDisplay, "%d.%d", int(max_o3_ppb/1000), int(max_o3_ppb%1000));
  }
  myNex.writeStr("dl.smaxppm.txt", tempStringDisplay);

  myNex.writeNum("dl.npm25.val", pm25Display);
  myNex.writeNum("dl.npm1.val", pm1Display);
  myNex.writeNum("dl.npm10.val", pm10Display); 

  sprintf(tempStringDisplay, "%d", pm1Display);
  myNex.writeStr("dl.spm1.txt", tempStringDisplay);

  sprintf(tempStringDisplay,"%d", pm25Display);
  myNex.writeStr("dl.spm25.txt", tempStringDisplay);

  sprintf(tempStringDisplay,"%d", pm10Display);
  myNex.writeStr("dl.spm10.txt", tempStringDisplay);

  sprintf(tempStringDisplay, "%d", max_pm25);
  myNex.writeStr("dl.maxpm25.txt", tempStringDisplay);

  sprintf(tempStringDisplay,"%d", min_pm25);
  myNex.writeStr("dl.minpm25.txt", tempStringDisplay);

}
