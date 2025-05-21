#include <Arduino.h>
#include <string.h>
#include "./Types/Smiley.h"
#include <ctime>
#include "./Services/APService.h"
#include "./Services/NTPService.h"
#include "./Types/Debounce.h"

#define BLUE_BUTTON 26
#define BLUE_LED 4
#define RED_BUTTON 33
#define RED_LED 18
#define GREEN_BUTTON 27
#define GREEN_LED 19
#define YELLOW_BUTTON 25
#define YELLOW_LED 21

void registerSmileys();
Debounce debounce(0, 0);

Smiley smileys[] = {
    Smiley(RED_BUTTON, SMILEY_TYPE_ANGRY, RED_LED),
    Smiley(YELLOW_BUTTON, SMILEY_TYPE_SAD, YELLOW_LED),
    Smiley(BLUE_BUTTON, SMILEY_TYPE_MEH, BLUE_LED),
    Smiley(GREEN_BUTTON, SMILEY_TYPE_HAPPY, GREEN_LED)};

void setup()
{
  Serial.begin(115200);
  // Register Smileys
  registerSmileys();

  Smiley id;
  unsigned long now;
  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT1)
  {

    for (Smiley smiley : smileys)
    {
      if (digitalRead(smiley.getButtonId()) == HIGH)
      {
        if (debounce.isDebounced(smiley.getButtonId(), millis()))
        {
          return;
        }

        debounce.button_id = smiley.getButtonId();
        debounce.last_time = millis();
        now = millis();

        digitalWrite(smiley.getLightId(), HIGH);
        Serial.printf("Button %d pressed, light %d ON\n", smiley.getButtonId(), smiley.getLightId());
        id = smiley;
        break;
      }
    }
  }

  if (!APService::isConnected())
  {
    APService::setup();
    NTPService::setup();
  }

  if (id.getButtonId() != 0)
  {
    id.setTimestamp(NTPService::getTime());
    while (millis() < now + 7000)
    {
    }
    digitalWrite(id.getLightId(), LOW);
  }

  uint64_t wakeupPins = 0;
  for (Smiley smiley : smileys)
  {
    wakeupPins |= (1ULL << smiley.getButtonId());
  }

  esp_sleep_enable_ext1_wakeup(wakeupPins, ESP_EXT1_WAKEUP_ANY_HIGH);

  // Enter deep sleep
  Serial.println("Entering deep sleep...");
  delay(100);
  esp_deep_sleep_start();
}

void loop()
{
}

void registerSmileys()
{
  for (Smiley smiley : smileys)
  {
    pinMode(smiley.getButtonId(), INPUT);
    pinMode(smiley.getLightId(), OUTPUT);
    // smiley.setTimestamp(NTPService::getTime());
    //  Serial.printf("Button ID: %d, Light ID: %d Timestamp: %s\n", smiley.getButtonId(), smiley.getLightId(), asctime(smiley.getTimestamp()));
  }
}