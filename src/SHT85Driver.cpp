#include "SHT85Driver.h"
#include "config.h"

uint lastReadSHT 	= 0;
float TemDisplay 		= 0;
float TemDisplay_F  = 0;
float HumDisplay 		= 0;
void SHT_GetData()
{
  if ( (millis() - lastReadSHT > 5000) || (millis() < lastReadSHT))
  {
    float SHT_temp = 0;
    float SHT_humi = 0;
#ifdef	DEBUG_SERIAL

      Serial.print("teeeemp: ");
      Serial.println(tempCalibInt);
      Serial.print("humiiiii: ");
      Serial.println(humiCalibInt);
#endif
    if (sht.readSample()) {

      SHT_temp = sht.getTemperature()+ tempCalibInt;
      SHT_humi = sht.getHumidity() + humiCalibInt;
#ifdef	DEBUG_SERIAL
      Serial.println("T = "+String(SHT_temp)+"  "+"H = "+String(SHT_humi));
#endif
    } else {
#ifdef	DEBUG_SERIAL
      Serial.print("SHT85 Error in readSample()\n");   
#endif
    }
    if(SHT_temp>0 && SHT_humi>0 && SHT_temp<100 && SHT_humi<100){
      TemDisplay = SHT_temp ;
      HumDisplay = SHT_humi ;
      TemDisplay_F = SHT_temp + 273;
    }else{
      TemDisplay = 0;
      HumDisplay = 0;     
    }
    lastReadSHT = millis(); 
  }
}


void SHT_Init(){
  if (sht.init()) {
#ifdef	DEBUG_SERIAL
    Serial.print("SHT init(): success\n");
#endif
  } else 
  {
#ifdef	DEBUG_SERIAL
  Serial.print("SHT init(): failed\n");
#endif
  }
}
