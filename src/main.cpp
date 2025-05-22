#include <Arduino.h>
#include <string.h>
#include "./Types/Smiley.h"
#include <ctime>
#include "./Services/APService.h"
#include "./Services/NTPService.h"
#include "./Services/MQTTService.h"
#include "./Types/Debounce.h"

#define BUTTON_PIN_BITMASK(GPIO) (1ULL << GPIO)
#define BLUE_BUTTON 26
#define BLUE_LED 4
#define RED_BUTTON 33
#define RED_LED 18
#define GREEN_BUTTON 27
#define GREEN_LED 19
#define YELLOW_BUTTON 25
#define YELLOW_LED 21

void registerSmileys();
void registerWakeupPins();

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
  bool pressed = false;
  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT1)
  {
    uint64_t wakeupPin = esp_sleep_get_ext1_wakeup_status();
    for (Smiley smiley : smileys)
    {
      if (wakeupPin & BUTTON_PIN_BITMASK(smiley.getButtonId()))
      {
        // Check if the button is debounced
        if (debounce.isDebounced(smiley.getButtonId(), millis()))
        {
          return;
        }

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

  if (!MQTTService::isConnected())
  {
    MQTTService::setup();
  }

  if (id.getButtonId() != 0)
  {
    id.setTimestamp(NTPService::getTime());
    if (MQTTService::sendMessage(id.toJson()))
    {
      Serial.println("Message sent successfully");
    }
    else
    {
      Serial.println("Failed to send message");
    }
    unsigned long sleepTime = debounce.last_time + 7000;
    while (millis() < sleepTime)
    {
    }

    digitalWrite(id.getLightId(), LOW);
  }

  registerWakeupPins();

  // Enter deep sleep
  Serial.println("Entering deep sleep...");
  delay(100);
  esp_deep_sleep_start();
}

void registerWakeupPins()
{
  uint64_t wakeupPins = 0;
  for (Smiley smiley : smileys)
  {
    wakeupPins |= BUTTON_PIN_BITMASK(smiley.getButtonId());
  }

  esp_sleep_enable_ext1_wakeup(wakeupPins, ESP_EXT1_WAKEUP_ANY_HIGH);
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