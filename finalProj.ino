#include <Freenove_WS2812_Lib_for_ESP32.h>
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define SDA 13 
#define SCL 14
#define LEDS_COUNT  8  
#define LEDS_PIN    2  
#define CHANNEL     0 

LiquidCrystal_I2C lcd(0x27,16,2);
Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

const char* ssid = "myguestnetwork";
const char* password = "mnwguest";
WiFiUDP Udp;
unsigned int localUdpPort = 4210; 
char incomingPacket[255];  
int temp2;
int uptownState = 0;
int downtownState = 1;

void setup() {
  int status = WL_IDLE_STATUS;
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("");

  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);

  Wire.begin(SDA, SCL);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to wifi");
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

  // we recv one packet from the remote so we can know its IP and port
  bool readPacket = false;
  while (!readPacket) {
    int packetSize = Udp.parsePacket();
    if (packetSize)
     {
      // receive incoming UDP packets
      Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
      int len = Udp.read(incomingPacket, 255);
      if (len > 0)
      {
        incomingPacket[len] = 0;
      }
      Serial.printf("UDP packet contents: %s\n", incomingPacket);
      String temp = String(incomingPacket);
      temp2 =  temp.toInt();
      readPacket = true;
    } 
  }
   // once we know where we got the inital packet from, send data back to that IP address and port
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Udp.printf("hi");
  Udp.endPacket();
  delay(1000);
}

void loop() {
if(temp2>10 ){
  int j = temp2/10;
  if(j>10){
    j=8;
  }
  strip.begin();
  for(int i = 0; i<j;i++){
   strip.setLedColorData(i, 0, 0, 255);
   strip.show();
   delay(500); 
  }
}
  bool readPacket = false;
  while (!readPacket) {
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
      // receive incoming UDP packets
      Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
      int len = Udp.read(incomingPacket, 255);
      if (len > 0)
      {
        incomingPacket[len] = 0;
      }
     // Serial.printf("UDP packet contents: %s\n", incomingPacket);
      lcd.setCursor(0,0);
      lcd.print(incomingPacket);
      
      readPacket = true; 
    }
    else{
     readPacket = true;  
    }
  }
  int buttonQ = digitalRead(25);
  int buttonB = digitalRead(26);
  
  if (buttonQ == 0){
    int switchState = digitalRead(27);
    if(switchState == uptownState){
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.printf("qn");
        Udp.endPacket();
        delay(500);
    }
    else if(switchState == downtownState){
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.printf("qs");
        Udp.endPacket();
        delay(500);
    }
  }
  
  if(buttonB == 0){
    int switchState = digitalRead(27);
    if(switchState == uptownState){
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.printf("bn");
        Udp.endPacket();
        delay(500);
    }
    else if(switchState == downtownState){
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.printf("bs");
        Udp.endPacket();
      delay(500);
    }
  }
  readPacket = false;
  while (!readPacket) {
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
      // receive incoming UDP packets
      Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
      int len = Udp.read(incomingPacket, 255);
      if (len > 0)
      {
        incomingPacket[len] = 0;
      }
     // Serial.printf("UDP packet contents: %s\n", incomingPacket);
      lcd.setCursor(0,1);
      lcd.print(incomingPacket);
      readPacket = true; 
    }
    else{
     readPacket = true;  
    }
  }
  delay(500);
}
