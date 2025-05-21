#include <Arduino.h>
#include <string.h>
#include "./Types/Smiley.h"
#include <ctime>
#include "./Services/APService.h"
#include "./Services/NTPService.h"


#define BLUE_BUTTON 26
#define BLUE_LED 4
#define RED_BUTTON 33
#define RED_LED 18
#define GREEN_BUTTON 27
#define GREEN_LED 19
#define YELLOW_BUTTON 25
#define YELLOW_LED 5

void registerSmileys();


Smiley smiley[] = {
    Smiley(RED_BUTTON, SMILEY_TYPE_ANGRY, RED_LED),
    Smiley(YELLOW_BUTTON, SMILEY_TYPE_SAD, YELLOW_LED),
    Smiley(BLUE_BUTTON, SMILEY_TYPE_MEH, BLUE_LED),
    Smiley(GREEN_BUTTON, SMILEY_TYPE_HAPPY, GREEN_LED)
};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting setup of AP...");
    //Register Smileys
  registerSmileys();

  Smiley id;
    if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT1) {
      bool found = false;

    for (Smiley smiley : smiley) {
      if (digitalRead(smiley.getButtonId()) == HIGH) { 
        digitalWrite(smiley.getLightId(), HIGH);
        Serial.printf("Button %d pressed, light %d ON\n", smiley.getButtonId(), smiley.getLightId());
        delay(1000); // Keep the light on for 1 second
        digitalWrite(smiley.getLightId(), LOW);
        id = smiley;
        found = true;
        break;
      }
      if (found) break;
    }
  }


  //Initialize services
  APService::setup();
  NTPService::setup();
  id.setTimestamp(NTPService::getTime());


  
  Serial.printf("Type: %d", esp_sleep_get_wakeup_cause());


  // registers pins used for waking up program
  uint64_t wakeupPins = 0;
  for (Smiley smiley : smiley) {
    wakeupPins |= (1ULL << smiley.getButtonId());
  }

    esp_sleep_enable_ext1_wakeup(wakeupPins, ESP_EXT1_WAKEUP_ANY_HIGH);  

  // Enter deep sleep
  Serial.println("Entering deep sleep...");
  delay(100);
  esp_deep_sleep_start();
  
}

void loop() {
}

void registerSmileys() {
  for (Smiley smiley : smiley) {
    pinMode(smiley.getButtonId(), INPUT_PULLUP);
    pinMode(smiley.getLightId(), OUTPUT);
    //smiley.setTimestamp(NTPService::getTime());
    // Serial.printf("Button ID: %d, Light ID: %d Timestamp: %s\n", smiley.getButtonId(), smiley.getLightId(), asctime(smiley.getTimestamp()));
  }
}