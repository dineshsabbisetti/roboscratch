/************************************************************** 
 * IoT Temperature Monitor with Blynk
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 * 
 * Developed by Dinesh - 10 February 2020
 ***************************************************************/
/* ESP & Blynk */
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
char auth[] = "bA1b2MGcNNHvoiwpKKOw3YOBCteoY0kE";

/* WiFi credentials */
char ssid[] = "SMARTFISH";
char pass[] = "smartfish@123";

/* TIMER */
#include <SimpleTimer.h>
SimpleTimer timer;

/* DS18B20 Temperature Sensor */
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2 // DS18B20 on arduino pin2 corresponds to D4 on physical board
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
float temp;

float Sensor_1 = 0;
float Sensor_2 = 0;
float Sensor_3 = 0;
float Sensor_4 = 0;

float Sensor_1map = 0;
float Sensor_2map = 0;
float Sensor_3map = 0;
float Sensor_4map = 0;

float Sensor_1point = 0;
float Sensor_2point = 0;
float Sensor_3point = 0;
float Sensor_4point = 0;

int Pin_D5 = 14; //14 is a Gpio pin number label as D5
int Pin_D6 = 12; //12 is a Gpio pin number label as D6
int Pin_D7 = 13; //13 is a Gpio pin number label as D7

void setup() 
{
  
  Serial.begin(115200);
  pinMode(Pin_D5,OUTPUT);
  pinMode(Pin_D6,OUTPUT);
  pinMode(Pin_D7,OUTPUT);
  pinMode(A0,INPUT);
  Blynk.begin(auth, ssid, pass);
  DS18B20.begin();
  timer.setInterval(1000L, getSendData);
}

void loop() 
{
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
  
  //Repeat for Sensor_1
  digitalWrite(Pin_D5, LOW);     //Turn D5 Off
  digitalWrite(Pin_D6, LOW);     //Turn D5 off
  digitalWrite(Pin_D7, LOW);     //Turn D5 Off
  delay(300);                     //Wait for sensor
  Sensor_1 = analogRead(0);       //Read Analog pin as SENSOR4
  //Repeat for Sensor_2
  digitalWrite(Pin_D5, LOW);     //Turn D5 Off
  digitalWrite(Pin_D6, LOW);     //Turn D5 Off
  digitalWrite(Pin_D7, HIGH);     //Turn D5 On
  delay(300);                     //Wait for sensor
  Sensor_2 = analogRead(0);       //Read Analog pin as SENSOR1
  //Repeat for Sensor_3
  digitalWrite(Pin_D5, LOW);     //Turn D5 Off
  digitalWrite(Pin_D6, HIGH);     //Turn D5 On
  digitalWrite(Pin_D7, LOW);     //Turn D5 Off
  delay(300);                     //Wait for sensor
  Sensor_3 = analogRead(0);       //Read Analog pin as SENSOR2
  //Repeat for Sensor_4
  digitalWrite(Pin_D5, LOW);     //Turn D5 Off
  digitalWrite(Pin_D6, HIGH);     //Turn D5 On
  digitalWrite(Pin_D7, HIGH);     //Turn D5 On
  delay(300);                     //Wait for sensor
  Sensor_4 = analogRead(0);       //Read Analog pin as SENSOR3

  Sensor_1map = map(Sensor_1, 0, 1023, 0, 1000);
  Sensor_2map = map(Sensor_2, 0, 1023, 0, 1000);
  Sensor_3map = map(Sensor_3, 700, 1023, 0, 4000);
  Sensor_4map = map(Sensor_4, 0, 1023, 0, 1000);
  //Print the results to the serial monitor
  
  Serial.print(" \n Sensor1=");   
  Serial.print(Sensor_1);
  Serial.print(" \n Sensor2=");   
  Serial.print(Sensor_2);
  Serial.print(" \n Sensor3=");   
  Serial.print(Sensor_3);
  Serial.print(" \n Sensor4=");   
  Serial.print(Sensor_4);


  Serial.print(" \n Sensor1map=");   
  Serial.print(Sensor_1map);
  Serial.print(" \n Sensor2map=");   
  Serial.print(Sensor_2map);
  Serial.print(" \n Senso3map=");   
  Serial.print(Sensor_3map);
  Serial.print(" \n Sensor4map=");   
  Serial.print(Sensor_4map);
 
 
  Sensor_1point = Sensor_1map/100;
  Sensor_2point = Sensor_2map/100;
  Sensor_3point = Sensor_3map;
  Sensor_4point = Sensor_4map/100;


  Serial.print(" \n Sensor1point=");   
  Serial.print(Sensor_4point);
  Serial.print(" \n Sensor2point=");   
  Serial.print(Sensor_2point);
  Serial.print(" \n Sensor3point=");   
  Serial.print(Sensor_3point);
  Serial.print(" \n Sensor4point=");   
  Serial.print(Sensor_4point);
 
 
  Blynk.virtualWrite(V18, Sensor_1);  //Write values to Blynk server
  Blynk.virtualWrite(V19, Sensor_2);  //Write values to Blynk server
  Blynk.virtualWrite(V20, Sensor_3);  //Write values to Blynk server
  Blynk.virtualWrite(V21, Sensor_4);  //Write values to Blynk server
   
  
  Blynk.virtualWrite(V1, Sensor_1map);  //Write values to Blynk serve
  Blynk.virtualWrite(V2, Sensor_2map);  //Write values to Blynk serve
  Blynk.virtualWrite(V3, Sensor_3map);  //Write values to Blynk serve
  Blynk.virtualWrite(V4, Sensor_4map);  //Write values to Blynk serve
  
  
  Blynk.virtualWrite(V5, Sensor_1point);  //Write values to Blynk server
  Blynk.virtualWrite(V6, Sensor_1point);  //Write values to Blynk server
  Blynk.virtualWrite(V7, Sensor_1point);  //Write values to Blynk server
  Blynk.virtualWrite(V8, Sensor_1point);  //Write values to Blynk server
  
//  Blynk.virtualWrite(V19, Sensor_2);  //Write values to Blynk server
//  Blynk.virtualWrite(V20, Value_D7);  //Write values to Blynk server
//  Blynk.virtualWrite(V21, Value_D8);  //Write values to Blynk server
  
}
/***************************************************
 * Send temperature Sensor data to Blynk
 **************************************************/
void getSendData()
{
  DS18B20.requestTemperatures(); 
  temp = DS18B20.getTempCByIndex(0);
  Serial.print(" \n temperature=");   
  Serial.println(temp);
  Blynk.virtualWrite(V10, temp); //virtual pin V10
}