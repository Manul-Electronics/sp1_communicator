#include <WiFi.h>
#include <Preferences.h>
#include <Adafruit_NeoPixel.h>

#define STATUS_LED_PIN 4
#define RTS_PIN 5
#define DSMR_TX 6
#define SLEEP_TIME_MS 600000

Adafruit_NeoPixel status_led(1, STATUS_LED_PIN, NEO_GRB + NEO_KHZ800);
Preferences prefs;

bool isUSBConnected = false;
bool isWLConnected = false;

typedef enum {
  IDLE,
  CONFIG,
  SETUP,
  WIFI_CONFIG,
  WIFI_CONFIG_DONE,
  READ_DATA,
} PGM_STATE;

PGM_STATE currentState = IDLE;

int checkUSB(void){
    uint32_t *aa = USB_SERIAL_JTAG_FRAM_NUM_REG;
    uint32_t first = *aa;
    vTaskDelay(pdMS_TO_TICKS(10));
    return (int) (*aa - first);
}

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

void setup() {
  if(checkUSB() > 0){
    isUSBConnected = true;
    Serial.begin(115200); 
    currentState = CONFIG;   
  }
  else{
    currentState = WIFI_CONFIG_DONE;
  }
  
  Serial1.begin(115200, SERIAL_8N1, DSMR_TX, -1, false, 11000UL);
  status_led.begin();
  pinMode(RTS_PIN, OUTPUT);
  digitalWrite(RTS_PIN, LOW);
  prefs.begin("sys");
}

void loop() { 
  switch(currentState){
    case CONFIG:
      if(Serial.available() > 0){
        String rawCommand = Serial.readStringUntil('\n');

        String cmd = rawCommand.substring(0, rawCommand.indexOf(' '));
        String arg = rawCommand.substring(rawCommand.indexOf(' '), rawCommand.length());

        if(cmd == "set_ssid"){
          if(arg != ""){
            prefs.putString("ssid", arg);
            if(prefs.getString("ssid", "") == arg){
              Serial.printf("INF/set_ssid/OK");
            }
            else{
              Serial.printf("ERR/could_not_set_properties");
            }            
          }
          else{
            Serial.println("ERR/empty_arg");
          }
        }
        else if(cmd == "set_passphrase"){
          if(arg != ""){
            prefs.putString("pwd", arg);
            if(prefs.getString("pwd", "") == arg){
              Serial.printf("INF/set_passphrase/OK");
            }
            else{
              Serial.printf("ERR/could_not_set_properties");
            }
          }
          else{
            Serial.println("ERR/empty_arg");            
          }
        }
        else if(cmd == "get_network"){
          Serial.printf("INF/registered_network/%s", prefs.getString("ssid","null"));
        }
        else{
            Serial.println("ERR/unknown_command");          
        }
      }
      break;
    case WIFI_CONFIG:
      WiFi.mode(WIFI_STA);
      break;

    case READ_DATA:
      break;

    case IDLE;
  }
}
