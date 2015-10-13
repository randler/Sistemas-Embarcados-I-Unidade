#include <Wire.h>
#include "ADXL345.h"

ADXL345 acel = ADXL345();

struct Eixo{
  int acelX, acelY, acelZ;
  //int giroX, giroY, giroZ;
  };

  Eixo eixos;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  acel.powerOn();

}
void enviarEixos(){
    int tam =sizeof(eixos);
    char buff[tam];
    
    memcpy(&buff, &eixos, tam);

    Serial.write('I');
    Serial.write((uint8_t*)&buff,tam);
    Serial.write('F');
    
  }

void loop() {
  // put your main code here, to run repeatedly:
  acel.readAccel(&eixos.acelX, &eixos.acelY, &eixos.acelZ);

  enviarEixos();
  
  delay(50);
}
