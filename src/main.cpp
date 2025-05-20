#include <Arduino.h>
#include <string.h>
#include "./Types/Smiley.h"
// put function declarations here:
#define BLUE_BUTTON 19
#define BLUE_LED 18
#define RED_BUTTON 23
#define RED_LED 17
#define GREEN_BUTTON 22
#define GREEN_LED 16
#define YELLOW_BUTTON 21
#define YELLOW_LED 15
void registerSmileys();

Smiley smiley[] = {
    Smiley(RED_BUTTON, SMILEY_TYPE_ANGRY, RED_LED),
    Smiley(YELLOW_BUTTON, SMILEY_TYPE_SAD, YELLOW_LED),
    Smiley(BLUE_BUTTON, SMILEY_TYPE_MEH, BLUE_LED),
    Smiley(GREEN_BUTTON, SMILEY_TYPE_HAPPY, GREEN_LED)
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  registerSmileys();
}

void loop() {
  Serial.printf("Status: %s\n", digitalRead(BLUE_BUTTON) ? "pressed" : "not pressed");
  delay(1000);
}

void registerSmileys() {
  for (Smiley smiley : smiley) {
    pinMode(smiley.getButtonId(), INPUT_PULLUP);
    pinMode(smiley.getLightId(), OUTPUT);
  }
}