#include <ClosedCube_MAX30205.h>

#include <SPI.h>
#include "MQ135.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
ClosedCube_MAX30205 max30205;
const bool fahrenheittemp = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Init");
  max30205.begin(0x4C);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  display.clearDisplay();
  MQ135 gasSensor = MQ135(A0); // Attach sensor to pin A0
  float gasInfo = getGasSensorInfo(gasSensor);
  float tempInfo = getTempSensorInfo();
  Serial.print("Temp:");Serial.println(tempInfo);
  Serial.print("Gas:");Serial.println(gasInfo);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Pulse:");
  display.print("Temp:");display.println(tempInfo);
  display.print("Gas:");display.println(gasInfo);
  display.display();
  delete &gasSensor;
  delay(1000);

}

float getGasSensorInfo(MQ135 sensor){
  return sensor.getRZero();
}

float getTempSensorInfo(){
  float temp = max30205.readTemperature(); // считываем температуру каждые 5ms
  if( fahrenheittemp == true){
    temp = (temp * 1.8) + 32 ; // преобразуем температуру из Celcius (градусов Цельсия) в Farenhite (фаренгейты) используя формулу [ T(°C) × 1.8 + 32 ]
    return temp;
  }else{
    return temp;
  }
}
