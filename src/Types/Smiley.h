#pragma once
#include <ctime>
#include "./SmileyType.h"
#include "../Services/NTPService.h"
#include <ezButton.h>
class Smiley
{
public:
    Smiley() : button(0) {}
    Smiley(int button_id, SmileyType type, int light_id)
        : button_id(button_id), type(type), light_id(light_id) {
            button = new ezButton(button_id);
        }
    int getButtonId() const { return button_id; }
    ezButton* getButton() const { return button; }
    SmileyType getType() const { return type; }
    int getLightId() const { return light_id; }
    struct tm* getTimestamp() const { return timestamp; }
    void setTimestamp(struct tm* new_timestamp) { timestamp = new_timestamp; }

private:
    int button_id;
    ezButton* button;
    SmileyType type;
    int light_id;
    struct tm* timestamp;
};
