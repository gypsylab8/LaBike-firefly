
//********************************************
//-------------------------------------------
//********************************************
// Wearable << Firefly 0.1.1 >> VestSign

// #LaBike <<(+) gadgets 4 Bikes&Bikers (+)>> 
// by @GuimaSan 201801 - [CC BY NC]
// @GypsyLab8
// SESCConsolacao Sao Paulo SP BR

// !! ->>> Sensor Model GY521 >> pins 2 and 3 
// Referece MPU-6050 
// By Arduino User JohnChi
// August 17, 2014
// Public Domain

//********************************************
//-------------------------------------------
//********************************************


#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

//LED's Right and Left
int R = 8; 
int L = 14;

//STOP RED LED's
int SR = 16;
int SL = 4; 

void setup(){
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);

  digitalWrite(4, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);
  digitalWrite(16, LOW);
  
  
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);    // 9600 

  
}
void loop(){
 
  digitalWrite(4, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);
  digitalWrite(16, LOW);
   
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  delay(333);

//LED Control
  if(AcY > 13000){
    for(int x = 0; x<10; x++){
      digitalWrite(L, HIGH);
      delay(100);
      digitalWrite(L, LOW);
      delay(400);
    } 
   }else if(AcY < -13000){
        for(int x = 0; x<10; x++){
          digitalWrite(R, HIGH);
          delay(100);
          digitalWrite(R, LOW);
          delay(400);
        } 
      }else if(AcX < -6000){
         for(int x = 0; x<10; x++){
          digitalWrite(SR, HIGH);
          digitalWrite(SL, HIGH);
          delay(100);
          digitalWrite(SR, LOW);
          digitalWrite(SL, LOW);
          delay(400);
          } 
        }else{
        digitalWrite(L, LOW);
        digitalWrite(R, LOW);
        digitalWrite(SL, LOW);
        digitalWrite(SR, LOW);
        }
  
}
