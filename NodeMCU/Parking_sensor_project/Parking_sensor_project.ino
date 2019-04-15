#include <stdint.h>
#include "Adafruit_VL53L0X.h"
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

//กำหนด address ของ sensor แต่ละตัว
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32

//กำหนดตัวแปร check ช่องว่างหรือไม่
int state1 = 0;
int state2 = 0;
int state3 = 0;
String state1Data;
String state2Data;
String state3Data;

//กำหนด shutdown pin ของ sensor
#define SHT_LOX1 D6
#define SHT_LOX2 D7
#define SHT_LOX3 D5

//objects สำหรับ sensor
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();

//กำหนดตัวแปรสำหรับการวัดค่า
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;

//กำหนดการเชื่อมต่อ WIFI
const char *ssid = "true_home2G_5FE"; // ชื่อ WiFi
const char *password = "06800727"; // password ของ WiFi
const char *host = "3.0.177.239"; // server address


//function เริ่มต้นสำหรับการ set การทำงานของ sensor เพื่อสามารถใช้ได้หลายตัว
void setID() {
  // reset sensor ทุกตัว
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  delay(10);
  // เปิดการทำงาน sensor ทุกตัว
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  // เปิดการทำงานของ sensor ตัวที่ 1
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);

  // check การเชื่อมต่อ sensor ตัวที่ 1
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  // เปิดการทำงานของ sensor ตัวที่ 2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  //check การเชื่อมต่อ sensor ตัวที่ 2
  if(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }

  // เปิดการทำงานของ sensor ตัวที่ 3
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  //check การเชื่อมต่อ sensor ตัวที่ 3
  if(!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot third VL53L0X"));
    while(1);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  
  //เชื่อมต่อ WIFI Router
  WiFi.begin(ssid, password); 
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  //กำหนด pin ของ sensor
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);

  //reset sensor ทุกตัวเมื่อเริ่มต้นการทำงานของ NodeMCU
  Serial.println("Shutdown pins inited...");
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);

  //ตั้งค่า sensor สำหรับการใช้งาน
  Serial.println("Starting...");
  setID();
}

void loop() {
// ส่วนของ Sensor
  //sensor ทำงานเพื่อรับค่าและแสดงผล
  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false);
  lox3.rangingTest(&measure3, false);

  //check ช่องว่างหรือไม่ (ว่าง = 1, ไม่ว่าง = 0)
  if(measure1.RangeStatus != 4){
    if(measure1.RangeMilliMeter <= 300){
      state1 = 0;
    }else {
      state1 = 1;
    } 
  } else {state1 = 1;}
  Serial.print("Sensor1: ");
  Serial.print(state1);

  if(measure2.RangeStatus != 4){
    if(measure2.RangeMilliMeter <= 300){
      state2 = 0;
    }else {
      state2 = 1;
    } 
  } else {state2 = 1;}
  Serial.print("  Sensor2: ");
  Serial.print(state2);

  if(measure3.RangeStatus != 4){
    if(measure3.RangeMilliMeter <= 300){
      state3 = 0;
    }else {
      state3 = 1;
    } 
  } else {state3 = 1;}
  Serial.print("  Sensor3: ");
  Serial.print(state3);
  Serial.println();


// ส่วนของการเชื่อมต่อและส่งค่าไปยัง database
  Serial.print("connecting to ");
  Serial.println(host);
  
  WiFiClient client;
  //กำหนด port
  const int httpPort = 80;

  // check การเชื่อมต่อ
  delay(1500);
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  //สร้าง url สำหรับส่งไปเพื่อเก็บค่าที่ database
  state1Data = String(state1);
  state2Data = String(state2);
  state3Data = String(state3);
  
  String url = "/get.php?d_status1=";
  url += state1Data;
  url += "&d_status2=";
  url += state2Data;
  url += "&d_status3=";
  url += state3Data;

  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  //ส่ง url ไปยัง server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
   
  Serial.println();
  Serial.println("closing connection");
  delay(3000);

}
