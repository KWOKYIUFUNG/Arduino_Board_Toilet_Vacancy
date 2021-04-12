
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

//sensor
#define SIGNAL_PIN 13  //PIR Sensor
const int sensor = 12; //Megnetic Sensor
int state; // 0 door close - 1 door open

//WIFI Setup

const char* ssid = "KKIF";
const char* password = "54001006";
WiFiClient client;

String apiKey = "W3DR5FAZX1KYNRID";
const char* server = "api.thingspeak.com";
int number = 1;
int i = 0;




void setup()
{
  pinMode(sensor, INPUT_PULLUP);
  pinMode(SIGNAL_PIN, INPUT);
  Serial.begin(115200);

  //WIFI

  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Print the IP address
  Serial.print("IP address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}





void loop()
{
  state = digitalRead(sensor);

  if (state == HIGH) {
    Serial.println("Door Open");
  }
  else {
    Serial.println("Door Close");
  }

  if (digitalRead(SIGNAL_PIN) == HIGH) {
    Serial.println("Movement detected.");
  } else {
    Serial.println("Did not detect movement.");
  }

  if (state != HIGH && digitalRead(SIGNAL_PIN) == HIGH) //Someone in the toilet
  {
    number = 0;
    
    //Update the data in thingspeak

    if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += int(number);
                             //postStr +="&field2="; //Reserved
                             //postStr += int(number); //Reserved
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("number: ");
                             Serial.print(number);
                             //Serial.print("Second number: "); //Reserved
                             //Serial.print(number); //Reserved
                             Serial.println(". Send to Thingspeak.");
                        }



    while (i=0){
      
    while(state != HIGH)//loop until the door open again
    {
      delay(2000);
    }

    delay(5000);
    if (digitalRead(SIGNAL_PIN) != HIGH)
    {
      i++;
    }
    
    }
    
  }
    //Someone left the toilet
    
    number = 1;
    
    //Update the data in Thingspeak
    
    if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += int(number);
                             //postStr +="&field2=";  //Reserved
                             //postStr += int(number); //Reserved
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("number: ");
                             Serial.print(number);
                             //Serial.print("Second number: "); //Reserved
                             //Serial.print(number); //Reserved
                             Serial.println(". Send to Thingspeak.");
                        }

    
  
      
  delay(2000);
}
