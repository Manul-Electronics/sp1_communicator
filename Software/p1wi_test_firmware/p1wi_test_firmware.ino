#include <WiFi.h>
#include "Adafruit_NeoPixel.h"
#include "status.h"

#define STATUS_LED_PIN 4
#define RTS_PIN 5
#define DSMR_TX 6

Adafruit_NeoPixel status_led(1, STATUS_LED_PIN, NEO_GRB + NEO_KHZ800);
Status status = Status(false, false, "-", false, "");

void WiFiEvent(WiFiEvent_t event){
  switch (event) {
      case ARDUINO_EVENT_WIFI_SCAN_DONE:
          Serial.println("Completed scan for access points");
          break;
      case ARDUINO_EVENT_WIFI_STA_START:
          Serial.println("WiFi client started");
          break;
      case ARDUINO_EVENT_WIFI_STA_STOP:
          Serial.println("WiFi clients stopped");
          break;
      case ARDUINO_EVENT_WIFI_STA_CONNECTED:
          Serial.println("Connected to access point");
          break;
      case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
          Serial.println("Disconnected from WiFi access point");
          break;
      case ARDUINO_EVENT_WIFI_STA_GOT_IP:
          Serial.print("Obtained IP address: ");
          Serial.println(WiFi.localIP());
          break;
      default:
        break;
  }  
}

void setup(){
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, DSMR_TX, -1, false, 11000UL);
  status_led.begin();
  pinMode(RTS_PIN, OUTPUT);
  digitalWrite(RTS_PIN, LOW);
  WiFi.onEvent(WiFiEvent);
}

void loop(){
  if(Serial.available() > 0){
    String rawCommand = Serial.readStringUntil('\n');

    String cmd = rawCommand.substring(0, rawCommand.indexOf(' '));
    String arg = rawCommand.substring(rawCommand.indexOf(' ')+1, rawCommand.length());

    if(cmd == "connect"){
      if(arg != ""){
        String ssid = arg.substring(0,arg.indexOf('|'));
        String passphrase = arg.substring(arg.indexOf('|')+1, arg.length());

        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid.c_str(), passphrase.c_str());

        char loadingChar[] = "/-\-";
        int index = 0;
        while(WiFi.status() != WL_CONNECTED){
          Serial.printf("\r%c Connecting...",loadingChar[index]);
          if(index < 3){
            index++;
          }
          else{
            index = 0;
          }
          delay(250);
        }
      }
    }
    else if(cmd == "status"){
      
    }
    else if(cmd == "read"){
      digitalWrite(RTS_PIN, HIGH);
      if(Serial1.available() > 0){
        
      }
    }
  }
}
