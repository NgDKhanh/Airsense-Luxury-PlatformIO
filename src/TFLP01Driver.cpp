#include "TFLP01Driver.h"
#include "config.h"


uint16_t crc16_modbus(char *modbusdata , uint16_t Length) 
{
  uint16_t i, j;
  uint16_t crc16 = 0xFFFF;
  for (i = 0; i < Length; i++)
  {
    crc16 ^= modbusdata[i];
    for (j = 0; j < 8; j++)
    {
      if ((crc16 & 0x01) == 1) crc16 = (crc16 >> 1) ^ 0xA001; 
      else
      crc16 >>= 1;
     }
  }
  return crc16;
}


void TFLP01_Init()
{
    Serial2.begin(115200);
}


void TFLP01_GetData()
{
  char TFLP01data[17] = {0};
  if (Serial2.available() > 0) 
  {  
    Serial.println("Check");
    for(char i=0; i<17; i++)
    {
      Serial.print(i);
      Serial.print(": ");
      byte tmp = Serial2.read();
      TFLP01data[i] = tmp;
      Serial.println(tmp);
    }
    
      TFLP01_read = true;
  }
//  while(Serial2.available() > 0) Serial2.read();
//      Serial.println(TFLP01data[15] + TFLP01data[16]<<8 );
//      Serial.println(crc16_modbus(TFLP01data, 15));
//    if (TFLP01data[15] + TFLP01data[16]<<8 == crc16_modbus(TFLP01data, 15))
//    {
//    }
  
  // lay du lieu tam thoi (chua co datasheet)
  if(TFLP01_read == true)
  {
    TFLP01_read = false;
    pm1Display  = TFLP01data[9]+TFLP01data[10]*256+pm1CalibInt;
    pm25Display = TFLP01data[11]+TFLP01data[12]*256+pm25CalibInt;
    pm10Display = TFLP01data[13]+TFLP01data[14]*256+pm10CalibInt;
    if(pm25Display!=255)
    {
      if(max_pm25 < pm25Display) max_pm25=pm25Display;
      if(min_pm25 > pm25Display) min_pm25=pm25Display;
    } 
#ifdef  DEBUG_SERIAL

    for(char i=0; i<17; i++)
    {
      Serial.print(i);
      Serial.print(": ");
      Serial.println(TFLP01data[i]);
    }
    Serial.println("Pm2.5:"+String(pm25Display)+" Pm10:"+String(pm10Display));

#endif
  }  
}
