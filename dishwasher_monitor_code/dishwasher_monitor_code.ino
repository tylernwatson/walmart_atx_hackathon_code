#include <SparkFun_MMA8452Q.h>
#include<stdio.h>
#include <SoftwareSerial.h>

MMA8452Q accel;
String orient;
SoftwareSerial lcd(2, 3);

//signed short minutes = 128;
char timeline[16];
byte dishwasher_status;
void setup() {
 // put your setup code here, to run once:
 Serial.begin(9600);
 lcd.begin(9600);
 clearDisplay();
 lcd.print("Dishwasher off.");
 accel.init(SCALE_2G, ODR_6);
 printOrientation();
}

void loop() {
 if (accel.available()) {
  signed short minutes = 1;
  signed short seconds = 10;

   accel.read();
 
 // put your main code here, to run repeatedly:
 byte pl=accel.readPL();
 printOrientation();

 if (Serial.available() >0) {
   // read the incoming byte:
   dishwasher_status = Serial.read()- '0';
 }
 String sensor_output=String(accel.cx*10000)+","+String(accel.cy*10000)+","+String(accel.cz*10000)+","+orient;
 Serial.println(sensor_output);

 if (Serial.available() >0) {
   // read the incoming byte:
   dishwasher_status = Serial.read()- '0';
 }
 
while (dishwasher_status == 1) {
  clearDisplay();
  // lcd.print(dishwasher_status);
//   sprintf(timeline,"Running         %0.3d mins %0.2d secs", minutes, seconds);
//   sprintf(timeline,"Running         %0.3d mins", minutes);
   String statement="Running         "+String(minutes)+" mins "+String(seconds)+" sec";
   lcd.print(statement);
   delay(1000);
//   delay(60000);
   seconds--;
//   minutes--;
   clearDisplay();
   if (seconds == -1) {
     seconds = 59;
     minutes --;
   }
   if (seconds == 00 and minutes == 00) {
//  if (minutes == 0) {
     dishwasher_status = 0;
     lcd.print("Dishwasher off.");
   }
 }
 
 }
}

void printOrientation()
{
// accel.readPL() will return a byte containing information
// about the orientation of the sensor. It will be either
// PORTRAIT_U, PORTRAIT_D, LANDSCAPE_R, LANDSCAPE_L, or
// LOCKOUT.
byte pl = accel.readPL();
switch (pl) {
case PORTRAIT_U:
  orient="Portrait Up";
  break;
case PORTRAIT_D:
  orient="Portrait Down";
  break;
case LANDSCAPE_R:
  orient="Landscape Right";
  break;
case LANDSCAPE_L:
  orient="Landscape Left";
  break;
case LOCKOUT:
  orient="Flat";
  break;
}
}

// This function clears the display ¯\_(ツ)_/¯
void clearDisplay() {
lcd.write(0xFE);  // send the special command
lcd.write(0x01);  // send the clear screen command
}
