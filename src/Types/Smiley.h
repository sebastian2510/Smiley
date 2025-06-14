#pragma once
#include <ctime>

#include "./SmileyType.h"
#include "../Services/NTPService.h"
#include <string.h>
class Smiley
{
public:
    Smiley()
    {
        button_id = 0;
        type = SMILEY_TYPE_NONE;
        light_id = 0;
        timestamp = nullptr;
    }
    Smiley(int button_id, SmileyType type, int light_id)
        : button_id(button_id), type(type), light_id(light_id) {}

    int getButtonId() const { return button_id; }
    SmileyType getType() const { return type; }
    int getLightId() const { return light_id; }
    struct tm *getTimestamp() const { return timestamp; }
    void setTimestamp(struct tm *new_timestamp) { timestamp = new_timestamp; }
    const char *toJson() const
    {
        static char buffer[256];

        char *newtime = asctime(getTimestamp());
        newtime[strlen(newtime) - 1] = '\0';

        sprintf(buffer,
                "{"
                "\'button_id\': %d, "
                "\'led_id\': %d, "
                "\'type:\': \'%s\', "
                "\'timestamp\': \'%s\'"
                "}",
                button_id, light_id, SmileyTypeToString(type), newtime);
        return buffer;
    }

private:
    int button_id;
    SmileyType type;
    int light_id;
    struct tm *timestamp;
};
