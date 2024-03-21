#include <WiFi.h>
#include <Preferences.h>
#include <Adafruit_NeoPixel.h>

#define STATUS_LED_PIN 4
#define RTS_PIN 5
#define SLEEP_TIME_MS 600000

Adafruit_NeoPixel status_led(1, STATUS_LED_PIN, NEO_GRB + NEO_KHZ800);
Preferences prefs;

bool isUSBConnected = false;
bool isWLConnected = false;

typedef enum {
  IDLE,
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

void setup() {
  // put your setup code here, to run once:
  if(checkUSB() > 0){
    isUSBConnected = true;
    Serial.begin(115200);    
  }
  
  Serial1.begin(115200, SERIAL_8N1, 6, -1, false,11000UL);
  status_led.begin();
  pinMode(RTS_PIN, OUTPUT);
  prefs.begin("sys");

  if(isUSBConnected){
    currentState = SETUP;
  }
}

void loop() {
  //Check 
  switch(currentState){
    case WIFI_CONFIG:
      
      break;

    case READ_DATA:
      break;

    case IDLE;
  }
}
