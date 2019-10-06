#include <Wire.h>
#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" 


#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    
#endif


MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high


#define OUTPUT_READABLE_YAWPITCHROLL
// for I2C
 
#define eeprom_address 0x50    // device address 
byte d=0;
 
void setup()
{
  Serial.begin(115200); // Initialize the serial
  Wire.begin();
 
  //write data out
  Serial.println("Writing data.");
  for (int i=0; i<10; i++)
  {
    writeData(i,i);
  }
  Serial.println("Complete");
  //read data back
  Serial.println("Reading data.");
  for (int i=0; i<10; i++)
  {
    Serial.print(i);
    Serial.print(" : ");
    d=readData(i);
    Serial.println(d, DEC);
  }
  Serial.println("Complete");
 
}
 
// writes a byte of data in memory location eaddress
void writeData(unsigned int eaddress, byte data)
{
  Wire.beginTransmission(eeprom_address);
  // set the pointer position
  Wire.write((int)(eaddress >> 8));
  Wire.write((int)(eaddress & 0xFF));
  Wire.write(data);
  Wire.endTransmission();
  delay(10);
}
 
// reads a byte of data from memory location eaddress
byte readData(unsigned int eaddress)
{
  byte result;
  Wire.beginTransmission(eeprom_address);
  // set the pointer position
  Wire.write((int)(eaddress >> 8));
  Wire.write((int)(eaddress & 0xFF));
  Wire.endTransmission();
  Wire.requestFrom(eeprom_address,1); // get the byte of data
  result = Wire.read();
  return result;
}
 
void loop()
{
}
