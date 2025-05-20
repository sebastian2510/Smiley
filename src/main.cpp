#include <Arduino.h>
#include <string.h>
#include "./Types/Smiley.h"
#include <ctime>
#include "./Services/APService.h"
#include "./Services/NTPService.h"

#define BLUE_BUTTON 4
#define BLUE_LED 26
#define RED_BUTTON 18
#define RED_LED 33
#define GREEN_BUTTON 19
#define GREEN_LED 27
#define YELLOW_BUTTON 5
#define YELLOW_LED 25
void registerSmileys();

Smiley smiley[] = {
    Smiley(RED_BUTTON, SMILEY_TYPE_ANGRY, RED_LED),
    Smiley(YELLOW_BUTTON, SMILEY_TYPE_SAD, YELLOW_LED),
    Smiley(BLUE_BUTTON, SMILEY_TYPE_MEH, BLUE_LED),
    Smiley(GREEN_BUTTON, SMILEY_TYPE_HAPPY, GREEN_LED)
};

void setup() {
  Serial.begin(115200);
  APService::setup();
  NTPService::setup();
  registerSmileys();
}

void loop() {
  for (Smiley smiley : smiley) {
    if (digitalRead(smiley.getButtonId()) == HIGH) {
      digitalWrite(smiley.getLightId(), HIGH);
      Serial.printf("Button %d pressed, light %d ON\n", smiley.getButtonId(), smiley.getLightId());
      delay(1000); // Keep the light on for 1 second
      digitalWrite(smiley.getLightId(), LOW);
    }
  }
}

void registerSmileys() {
  for (Smiley smiley : smiley) {
    pinMode(smiley.getButtonId(), INPUT_PULLUP);
    pinMode(smiley.getLightId(), OUTPUT);
    Serial.printf("Button ID: %d, Light ID: %d Timestamp: %s\n", smiley.getButtonId(), smiley.getLightId(), asctime(smiley.getTimestamp()));
  }
}