/*
  Read the 18 channels of spectral light over I2C using the Spectral Triad
  By: Nathan Seidle
  SparkFun Electronics
  Date: October 25th, 2018
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example takes all 18 readings, 372nm to 966nm, over I2C and outputs
  them to the serial port.
  
  Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/15050

  Hardware Connections:
  Plug a Qwiic cable into the Spectral Triad and a BlackBoard
  If you don't have a platform with a Qwiic connection use the SparkFun Qwiic Breadboard Jumper (https://www.sparkfun.com/products/14425)
  Open the serial monitor at 9600 baud to see the output
*/

#include "SparkFun_AS7265X.h" //Click here to get the library: http://librarymanager/All#SparkFun_AS7265X
#include <Wire.h>
#include "SparkFun_VEML6030_Ambient_Light_Sensor.h"

#define ADDR 0x27
#define AL_ADDR 0x48
#define PI 3.1415926535897932384626433832795

SparkFun_Ambient_Light light(AL_ADDR);
AS7265X sensor;

int FAST, value1, value2, value3;

// Possible values: .125, .25, 1, 2
// Both .125 and .25 should be used in most cases except darker rooms.
// A gain of 2 should only be used if the sensor will be covered by a dark
// glass.
float gain = .25;

// Possible integration times in milliseconds: 800, 400, 200, 100, 50, 25
// Higher times give higher resolutions and should be used in darker light. 
int time = 400;
long luxVal = 0; 


void setup() {
  Wire.begin(); 
  Serial.begin(9600);

  FAST=200; // delay in ms (milliseconds)

  Serial.println("AS7265x Spectral Triad Example");

  if(light.begin())
    Serial.println("Ready to sense some light!"); 
  else
    Serial.println("Could not communicate with the sensor!");

  if(sensor.begin() == false)
  {
    Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
    while(1);
  }

  light.setGain(gain);
  light.setIntegTime(time);

  Serial.println("Reading settings..."); 
  Serial.print("Gain: ");
  float gainVal = light.readGain();
  Serial.print(gainVal, 3); 
  Serial.print(" Integration Time: ");
  int timeVal = light.readIntegTime();
  Serial.println(timeVal);

  Serial.println("Lamp,KRIDA,LUX,A-410,B-435,C-460,D-485,E-510,F-535,G-560,H-585,R-610,I-645,S-680,J-705,T-730,U-760,V-810,W-860,K-900,L-940");
}

void loop() {
  
  delay(1000);
  Wire.beginTransmission(ADDR); // device address
  Wire.write(0x80);             // select 1st channel   
  Wire.write(100);               // write dimm value "100" to 1st channel
  Wire.write(0x81);             // select 2nd channel   
  Wire.write(100);               // write dimm value "100" to 2st channel
  Wire.write(0x82);             // select 3rd channel   
  Wire.write(100);               // write dimm value "100" to 3rd channel
  Wire.write(0x83);             // select 4th channel   
  Wire.write(100);               // write dimm value "100" to 4th channel
  Wire.endTransmission();  
  delay(5000);
      
  for (int lamp = 1; lamp <= 4; lamp++) {
  for (int i = 66; i >= 0; i--) {
  
  Serial.print(lamp);
  Serial.print(",");
    
  Serial.print(i);
  Serial.print(",");
  
  Wire.beginTransmission(ADDR); // device address
  switch (lamp)
  {
  case 1:
  Wire.write(0x80);             // select 1st channel
  goto level;
  case 2:
  Wire.write(0x81);             // select 2nd channel   
  goto level;
  case 3:
  Wire.write(0x82);             // select 3rd channel   
  goto level;
  case 4:
  Wire.write(0x83);             // select 4th channel   
  goto level;
  }   
  level:
  Wire.write(i);               // write dimm value "i" to 1st channe
  Wire.endTransmission();  
  delay(FAST);

  luxVal = light.readLight();
  Serial.print(luxVal);
  Serial.print(",");  

  sensor.takeMeasurements(); //This is a hard wait while all 18 channels are measured

  Serial.print(sensor.getCalibratedA());
  Serial.print(",");
  Serial.print(sensor.getCalibratedB());
  Serial.print(",");
  Serial.print(sensor.getCalibratedC());
  Serial.print(",");
  Serial.print(sensor.getCalibratedD());
  Serial.print(",");
  Serial.print(sensor.getCalibratedE());
  Serial.print(",");
  Serial.print(sensor.getCalibratedF());
  Serial.print(",");
  Serial.print(sensor.getCalibratedG());
  Serial.print(",");
  Serial.print(sensor.getCalibratedH());
  Serial.print(",");
  Serial.print(sensor.getCalibratedR());
  Serial.print(",");
  Serial.print(sensor.getCalibratedI());
  Serial.print(",");
  Serial.print(sensor.getCalibratedS());
  Serial.print(",");
  Serial.print(sensor.getCalibratedJ());
  Serial.print(",");
  Serial.print(sensor.getCalibratedT());
  Serial.print(",");
  Serial.print(sensor.getCalibratedU());
  Serial.print(",");
  Serial.print(sensor.getCalibratedV());
  Serial.print(",");
  Serial.print(sensor.getCalibratedW());
  Serial.print(",");
  Serial.print(sensor.getCalibratedK());
  Serial.print(",");
  Serial.print(sensor.getCalibratedL());
  Serial.print(",");


  Serial.println();
  
  if (i==0)
  {
  Wire.beginTransmission(ADDR); // device address
  Wire.write(0x80);             // select 1st channel   
  Wire.write(100);               // write dimm value "100" to 1st channel
  Wire.write(0x81);             // select 2nd channel   
  Wire.write(100);               // write dimm value "100" to 2st channel
  Wire.write(0x82);             // select 3rd channel   
  Wire.write(100);               // write dimm value "100" to 3rd channel
  Wire.write(0x83);             // select 4th channel   
  Wire.write(100);               // write dimm value "100" to 4th channel
  Wire.endTransmission();  
  delay(5000);
  }

  
  }
  }
}
