#include <QMC5883L.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>

int heading;

int angle;
int angleflag = 0;


char command; 
 


QMC5883L compass;


const int drive_distance = 50;   // cm
const int motor_power = 2048;      // 0-255
const int motor_soffset = 25; // spiin
const int motor_offset = 100;       // Diff. when driving straight
const int wheel_d = 200;           // Wheel diameter (mm)
const float wheel_c = PI * wheel_d; // Wheel circumference (mm)
const int counts_per_rev = 30;   // (4 pairs N-S) * (48:1 gearbox) * (2 falling/rising edges) = 384



const int enc_l_pin = 2;          // Motor A
const int enc_r_pin = 3;          // Motor B

const int vcc = 6;          // vcc
const int gnd = 7;          // Gnd




const int pwma_pin = 8;
const int ain1_pin = 9;
const int ain2_pin = 10;
const int pwmb_pin = 11;
const int bin1_pin = 12;
const int bin2_pin = 13;
const int stby_pin = 14;

volatile unsigned long enc_l = 0;
volatile unsigned long enc_r = 0;

int set1 = 0; 
int set2 = 0; 

int pot1 = A0;
int pot2 = A1;

uint32_t dac1_value = 0;
uint32_t dac2_value = 0; 

int sensorValue1 = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;  // variable to store the value coming from the sensor


Adafruit_MCP4725 dac1(4); // ADDR pin of MCP4725 connected to Arduino pin 2
Adafruit_MCP4725 dac2(5); // ADDR pin of MCP4725 connected to Arduino pin 3

void setup(void) {
  Serial.begin(9600); 
  
  pinMode(pwma_pin, OUTPUT); // no neeed
  pinMode(ain1_pin, OUTPUT);
  pinMode(ain2_pin, OUTPUT);
  pinMode(pwmb_pin, OUTPUT);
  pinMode(bin1_pin, OUTPUT);
  pinMode(bin2_pin, OUTPUT);
  pinMode(stby_pin, OUTPUT);
  
  pinMode(vcc, OUTPUT);
  pinMode(gnd, OUTPUT);
  digitalWrite(vcc, HIGH);
  digitalWrite(gnd, LOW);
  
  pinMode(enc_l_pin, INPUT_PULLUP);
  pinMode(enc_r_pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(enc_l_pin), countLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(enc_r_pin), countRight, CHANGE);
  
  Serial.println("Hello!");
  
  Wire.begin();

  compass.init();
  compass.setSamplingRate(50);
  
  Serial.println("QMC5883L Compass Demo");
  Serial.println("Turn compass in all directions to calibrate....");
  
  // The begin method must be called with the address of the MCP4725 when ADDR pin is tied to VCC
  // For Adafruit MCP4725A1 this is 0x63
  // For MCP4725A0 this is 0x61
  // For MCP4725A2 this is 0x65
  dac1.begin(0x60);
  dac2.begin(0x60);
  Serial.println("Example sketch demonstrating addressing multiple MCP4725s");
  dac1_value = 0;
  dac2_value = 0;
  dac1.setVoltage(dac1_value, false);
  dac2.setVoltage(dac2_value, false);
  
  delay(2000);
 
  //enableMotors(true);
//  driveForward(drive_distance, motor_power);
//  driveBack(drive_distance, motor_power);
//  driveRight(drive_distance, motor_power); 
//  driveLeft(drive_distance, motor_power);

  
}

void loop(void) {



  if(Serial.available() > 0){ 
    command = Serial.read(); 
    brake(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous.   
    //Serial.println(command);
    switch(command){
    case 'F':  
      driveForward(drive_distance, motor_power);
      break;
    case 'B':  
       driveBack(drive_distance, motor_power);
       break;
    case 'L':  
      driveLeft(33, motor_power);
      break;
    case 'R':
      driveRight(33, motor_power);
      break;
     case 't':
      brake(); ////////
      break;
     case 'N':
      angle = 360;
      Oritntation(angle);
      break;
     case 'E':
      angle =90;
      Oritntation(angle);
      break;   
     case 'S':
      angle =180;
      Oritntation(angle);
      break;   
     case 'W':
      angle =270;
      Oritntation(angle);
      break;      
            
    }
  } 

 






  
  
  heading = compass.readHeading();
  if(heading==0) {
    // Still calibrating, so measure but don't print 
  } else {
    Serial.println("heading");
    Serial.println(heading);
  }
  
  //sensorValue1 = analogRead(pot1);
  //sensorValue2 = analogRead(pot2);
  
  //set1 = map(sensorValue1, 0,1024, 0, 255);                    //steer 0 - 255
  //set2 = map(sensorValue2, 0,1024, 0, 255);                    //throttle 0 - 255


 // Serial.print("sensor1 = ");
 // Serial.print(sensorValue1);
 // Serial.print(" sensor2 = ");
 // Serial.println(sensorValue2);
 // Serial.println("\n");

 // dac1_value = map(set1, 255,0,0,4095);                 //steer amount 0 - 4095 
  //dac1.setVoltage(dac1_value, false);
 // dac2_value = map(set2, 255,0,0,4095);                 //steer amount 0 - 4095 
  //dac2.setVoltage(dac2_value, false);
  
  //FSerial.println(dac1_value); 
  //Serial.println(dac2_value);     

  Serial.print("enc_l= \t");
  Serial.print(enc_l);
  Serial.print("\t");
  Serial.print("enc_r= \t");
  Serial.print(enc_r);
  Serial.print("\n");

   delay(100);
   
}


////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////FORWARD/////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


void driveBack(float dist, int power) {

  unsigned long num_ticks_l;
  unsigned long num_ticks_r;

  // Set initial motor power
  int power_l = motor_power;
  int power_r = motor_power;

  // Used to determine which way to turn to adjust
  unsigned long diff_l;
  unsigned long diff_r;

  // Reset encoder counts
  enc_l = 0;
  enc_r = 0;

  // Remember previous encoder counts
  unsigned long enc_l_prev = enc_l;
  unsigned long enc_r_prev = enc_r;

  // Calculate target number of ticks
  float num_rev = (dist * 10) / wheel_c;  // Convert to mm
  unsigned long target_count = num_rev * counts_per_rev;
  
  // Debug
  Serial.print("Driving for ");
  Serial.print(dist);
  Serial.print(" cm (");
  Serial.print(target_count);
  Serial.print(" ticks) at ");
  Serial.print(power);
  Serial.println(" motor power");

  // Drive until one of the encoders reaches desired count
  while ( (enc_l < target_count) && (enc_r < target_count) ) {

    // Sample number of encoder ticks
    num_ticks_l = enc_l;
    num_ticks_r = enc_r;

    // Print out current number of ticks
    Serial.print(num_ticks_l);
    Serial.print("\t");
    Serial.println(num_ticks_r);

    // Drive
    driveB(power_l, power_r);

    // Number of ticks counted since last time
    diff_l = num_ticks_l - enc_l_prev;
    diff_r = num_ticks_r - enc_r_prev;

    // Store current tick counter for next time
    enc_l_prev = num_ticks_l;
    enc_r_prev = num_ticks_r;

    // If left is faster, slow it down and speed up right
    if ( diff_l > diff_r ) {
      power_l -= motor_offset;
      power_r += motor_offset;
    }

    // If right is faster, slow it down and speed up left
    if ( diff_l < diff_r ) {
      power_l += motor_offset;
      power_r -= motor_offset;
    }

    // Brief pause to let motors respond
    delay(20);
  }

  // Brake
  brake();
}



void driveB(int power_a, int power_b) {
  int ssteer = 2048;
  int steer = 0;
  // Constrain power to between -255 and 255
  power_a = constrain(power_a, -4096, 4096);
  power_b = constrain(power_b, -4096, 4096);

  // Set speed
  analogWrite(pwma_pin, abs(power_a));
  analogWrite(pwmb_pin, abs(power_b));


  int steer1 = abs(power_a);
  int steer2 = abs(power_b);

//  Serial.print("steer_1 = ");
//  Serial.print(steer1);
//  Serial.print("\t steer_2 = ");
//  Serial.print(steer2);
//  Serial.print("\n");

  dac1_value = 1024;
  dac2_value = steer1;
  dac1.setVoltage(dac1_value, false);
  dac2.setVoltage(dac2_value, false);
}
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////BACKWARD////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////



void driveForward(float dist, int power) {

  unsigned long num_ticks_l;
  unsigned long num_ticks_r;

  // Set initial motor power
  int power_l = motor_power;
  int power_r = motor_power;

  // Used to determine which way to turn to adjust
  unsigned long diff_l;
  unsigned long diff_r;

  // Reset encoder counts
  enc_l = 0;
  enc_r = 0;

  // Remember previous encoder counts
  unsigned long enc_l_prev = enc_l;
  unsigned long enc_r_prev = enc_r;

  // Calculate target number of ticks
  float num_rev = (dist * 10) / wheel_c;  // Convert to mm
  unsigned long target_count = num_rev * counts_per_rev;
  
  // Debug
  Serial.print("Driving for ");
  Serial.print(dist);
  Serial.print(" cm (");
  Serial.print(target_count);
  Serial.print(" ticks) at ");
  Serial.print(power);
  Serial.println(" motor power");

  // Drive until one of the encoders reaches desired count
  while ( (enc_l < target_count) && (enc_r < target_count) ) {

    // Sample number of encoder ticks
    num_ticks_l = enc_l;
    num_ticks_r = enc_r;

    // Print out current number of ticks
    Serial.print(num_ticks_l);
    Serial.print("\t");
    Serial.println(num_ticks_r);

    // Drive
    driveF(power_l, power_r);

    // Number of ticks counted since last time
    diff_l = num_ticks_l - enc_l_prev;
    diff_r = num_ticks_r - enc_r_prev;

    // Store current tick counter for next time
    enc_l_prev = num_ticks_l;
    enc_r_prev = num_ticks_r;

    // If left is faster, slow it down and speed up right
    if ( diff_l > diff_r ) {
      power_l -= motor_offset;
      power_r += motor_offset;
    }

    // If right is faster, slow it down and speed up left
    if ( diff_l < diff_r ) {
      power_l += motor_offset;
      power_r -= motor_offset;
    }

    // Brief pause to let motors respond
    delay(20);
  }

  // Brake
  brake();
}

void driveF(int power_a, int power_b) {
  int ssteer = 2048;
  int steer = 0;
  // Constrain power to between -255 and 255
  power_a = constrain(power_a, -4096, 4096);
  power_b = constrain(power_b, -4096, 4096);

  // Set speed
  analogWrite(pwma_pin, abs(power_a));
  analogWrite(pwmb_pin, abs(power_b));


  int steer1 = abs(power_a);
  int steer2 = abs(power_b);

//  Serial.print("steer_1 = ");
//  Serial.print(steer1);
//  Serial.print("\t steer_2 = ");
  Serial.print(steer2);
  Serial.print("\n");



  dac1_value = 1750;
  dac2_value = steer2;
  dac1.setVoltage(dac1_value, false);
  dac2.setVoltage(dac2_value, false);
}


////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////RIGHT///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////






void driveRight(float dist, int power) {

  unsigned long num_ticks_l;
  unsigned long num_ticks_r;

  // Set initial motor power
  int power_l = motor_power;
  int power_r = motor_power;

  // Used to determine which way to turn to adjust
  unsigned long diff_l;
  unsigned long diff_r;

  // Reset encoder counts
  enc_l = 0;
  enc_r = 0;

  // Remember previous encoder counts
  unsigned long enc_l_prev = enc_l;
  unsigned long enc_r_prev = enc_r;

  // Calculate target number of ticks
  float num_rev = (dist * 10) / wheel_c;  // Convert to mm
  unsigned long target_count = num_rev * counts_per_rev;
  
  // Debug
  Serial.print("Driving for ");
  Serial.print(dist);
  Serial.print(" cm (");
  Serial.print(target_count);
  Serial.print(" ticks) at ");
  Serial.print(power);
  Serial.println(" motor power");

  // Drive until one of the encoders reaches desired count
  while ( (enc_l < target_count) && (enc_r < target_count) ) {

    // Sample number of encoder ticks
    num_ticks_l = enc_l;
    num_ticks_r = enc_r;

    // Print out current number of ticks
    Serial.print(num_ticks_l);
    Serial.print("\t");
    Serial.println(num_ticks_r);

    // Drive
    driveR(power_l, power_r);

    // Number of ticks counted since last time
    diff_l = num_ticks_l - enc_l_prev;
    diff_r = num_ticks_r - enc_r_prev;

    // Store current tick counter for next time
    enc_l_prev = num_ticks_l;
    enc_r_prev = num_ticks_r;

    // If left is faster, slow it down and speed up right
    if ( diff_l > diff_r ) {
      power_l -= motor_soffset;
      power_r += motor_soffset;
    }

    // If right is faster, slow it down and speed up left
    if ( diff_l < diff_r ) {
      power_l += motor_soffset;
      power_r -= motor_soffset;
    }

    // Brief pause to let motors respond
    delay(20);
  }

  // Brake
  brake();
}




void driveR(int power_a, int power_b) {
  int ssteer = 2048;
  int steer = 0;
  // Constrain power to between -255 and 255
  power_a = constrain(power_a, -4096, 4096);
  power_b = constrain(power_b, -4096, 4096);

  // Set speed
  analogWrite(pwma_pin, abs(power_a));
  analogWrite(pwmb_pin, abs(power_b));


  int steer1 = abs(power_a);
  int steer2 = abs(power_b);

//  Serial.print("steer_1 = ");
//  Serial.print(steer1);
//  Serial.print("\t steer_2 = ");
//  Serial.print(steer2);
//  Serial.print("\n");
  
  steer = steer1 - 498;
  Serial.print("\t steer = ");
  Serial.print(steer);
  Serial.print("\n");
  dac1_value = steer;
  dac2_value = 1148;
  dac1.setVoltage(dac1_value, false);
  dac2.setVoltage(dac2_value, false);
}



////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////LEFT////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////




void driveLeft(float dist, int power) {

  unsigned long num_ticks_l;
  unsigned long num_ticks_r;

  // Set initial motor power
  int power_l = motor_power;
  int power_r = motor_power;

  // Used to determine which way to turn to adjust
  unsigned long diff_l;
  unsigned long diff_r;

  // Reset encoder counts
  enc_l = 0;
  enc_r = 0;

  // Remember previous encoder counts
  unsigned long enc_l_prev = enc_l;
  unsigned long enc_r_prev = enc_r;

  // Calculate target number of ticks
  float num_rev = (dist * 10) / wheel_c;  // Convert to mm
  unsigned long target_count = num_rev * counts_per_rev;
  
  // Debug
  Serial.print("Driving for ");
  Serial.print(dist);
  Serial.print(" cm (");
  Serial.print(target_count);
  Serial.print(" ticks) at ");
  Serial.print(power);
  Serial.println(" motor power");

  // Drive until one of the encoders reaches desired count
  while ( (enc_l < target_count) && (enc_r < target_count) ) {

    // Sample number of encoder ticks
    num_ticks_l = enc_l;
    num_ticks_r = enc_r;

    // Print out current number of ticks
    Serial.print(num_ticks_l);
    Serial.print("\t");
    Serial.println(num_ticks_r);

    // Drive
    driveL(power_l, power_r);

    // Number of ticks counted since last time
    diff_l = num_ticks_l - enc_l_prev;
    diff_r = num_ticks_r - enc_r_prev;

    // Store current tick counter for next time
    enc_l_prev = num_ticks_l;
    enc_r_prev = num_ticks_r;

    // If left is faster, slow it down and speed up right
    if ( diff_l > diff_r ) {
      power_l -= motor_soffset;
      power_r += motor_soffset;
    }

    // If right is faster, slow it down and speed up left
    if ( diff_l < diff_r ) {
      power_l += motor_soffset;
      power_r -= motor_soffset;
    }

    // Brief pause to let motors respond
    delay(20);
  }

  // Brake
  brake();
}

void driveL(int power_a, int power_b) {
  int ssteer = 2048;
  int steer = 0;
  // Constrain power to between -255 and 255
  power_a = constrain(power_a, -4096, 4096);
  power_b = constrain(power_b, -4096, 4096);

  // Set speed
  analogWrite(pwma_pin, abs(power_a));
  analogWrite(pwmb_pin, abs(power_b));


  int steer1 = abs(power_a);
  int steer2 = abs(power_b);

//  Serial.print("steer_1 = ");
//  Serial.print(steer1);
//  Serial.print("\t steer_2 = ");
//  Serial.print(steer2);
//  Serial.print("\n");
  steer = steer2 - 498;
  Serial.print("\t steer = ");
  Serial.print(steer);
  Serial.print("\n");
  
  dac1_value = steer;
  dac2_value = 2948;
  dac1.setVoltage(dac1_value, false);
  dac2.setVoltage(dac2_value, false);
}



void brake() {
  dac1_value = 0;
  dac2_value = 0;
  dac1.setVoltage(dac1_value, false);
  dac2.setVoltage(dac2_value, false);
  Serial.print("HOME");
}


////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////Spin////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


void Oritntation(int Angle_1)

{
int Difference = (Angle_1 - heading + 540) % 360 -180; // if difference is negative move left or else move right
int Tolerance1 = 1; 
int Tolerance2 = -1;



while (Difference < Tolerance2 || Difference > Tolerance1)
{
  angleflag = 0;
  heading = compass.readHeading();
  Difference =(Angle_1 - heading + 540) % 360 -180;

  Serial.print("diff");
  Serial.print(Difference);
  Serial.print("\n");

//int A =  Angle_1 - heading;
//int B =  Angle_1 - heading + 360;
//int G =  Angle_1 - heading - 360;
//int o = (Angle_1 - heading + 540) % 360 -180;

    // abs(power_a);
//
//  Serial.print("A B G");
//  Serial.print("\n");
//  Serial.print(A);
//  Serial.print("\n");
//  Serial.print(B);
//  Serial.print("\n");
//  Serial.print(G);
//  Serial.print("\n");
//  Serial.print(o);
//  Serial.print("\n");
//  


  
/*
 if ((Difference >= 90 && Difference < 180) || (Difference <= -90 && Difference > -180)){
 SpinRight(8);//20
 heading = compass.readHeading();


 
 //delay(1000);
 }
 
 if ((Difference >= 180 && Difference < 270) || (Difference <= -180 && Difference > -270)){
 SpinRight(15);//40
 heading = compass.readHeading();
 //delay(10);
 }
 
 if ((Difference >= 270 && Difference < 360) || (Difference <= -270 && Difference > -360)){
 SpinRight(20);//60
 heading = compass.readHeading();
 //delay(1000);
 }

if ((Difference >= 45 && Difference < 90) || (Difference <= -45 && Difference > -90)){
 SpinRight(10);//10
 heading = compass.readHeading();
 //delay(1000);
 }

 if ((Difference >= 10 && Difference < 45) || (Difference <= -10 && Difference > -45)){
 SpinRight(5);//5
 heading = compass.readHeading();
 //delay(1000);
 } 

if ((Difference >= 3 && Difference < 10) || (Difference <= -3 && Difference > -10)){
 SpinRight(3); //1
 heading = compass.readHeading();
 //delay(1000);
 } 

*/

 
 //////////////////////////////////////////////////////////////////////////// 
////////////////////////////////MINUS///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

if( Difference < 181 && Difference > 0){


if (Difference >= 90 && Difference < 181){
 SpinRight(10);//20
 heading = compass.readHeading();
 //delay(1000);
 }
 
// if (Difference >= 181 && Difference < 270){
// SpinRight(15);//40
// heading = compass.readHeading();
// //delay(10);
// }
// 
// if (Difference >= 270 && Difference < 360){
// SpinRight(20);//60
// heading = compass.readHeading();
// //delay(1000);
// }

if (Difference >= 45 && Difference < 90){
 SpinRight(10);//10
 heading = compass.readHeading();
 //delay(1000);
 }

 if (Difference >= 10 && Difference < 45){
 SpinRight(5);//5
 heading = compass.readHeading();
 //delay(1000);
 } 

if (Difference >= 3 && Difference < 10){
 SpinRight(3); //1
 heading = compass.readHeading();
  //delay(1000);
 } 

}

 
 //////////////////////////////////////////////////////////////////////////// 
////////////////////////////////MINUS///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

if( Difference > -181 && Difference < 0){

 if (Difference <= -90 && Difference > -181){
 SpinLeft(10);//20
 heading = compass.readHeading();
 //delay(1000);
 }
 
// if (Difference <= -181 && Difference > -270){
// SpinLeft(15);//40
// heading = compass.readHeading();
// //delay(10);
// }
// 
// if (Difference <= -270 && Difference > -360){
// SpinLeft(20);//60
// heading = compass.readHeading();
// //delay(1000);
// }

if (Difference <= -45 && Difference > -90){
 SpinLeft(10);//10
 heading = compass.readHeading();
 //delay(1000);
 }

 if (Difference <= -10 && Difference > -45){
 SpinLeft(5);//5
 heading = compass.readHeading();
 //delay(1000);
 } 

if (Difference <= -3 && Difference > -10){
 SpinLeft(3); //1
 heading = compass.readHeading();
 //delay(1000);
 } 

}

 
 //////////////////////////////////////////////////////////////////////////// 
////////////////////////////////MINUS///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////



}
}



void SpinRight(int steps) 
{
       driveRight(steps, motor_power);
}

void SpinLeft(int steps) 
{
       driveLeft(steps, motor_power);
}


















void countLeft() {
  enc_l++;
}

void countRight() {
  enc_r++;
}
