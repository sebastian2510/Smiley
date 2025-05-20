#pragma once
#include <ctime>
class Smiley {
public:
    Smiley(int button_id, SmileyType type, int light_id)
        : button_id(button_id), type(type), light_id(light_id), timestamp(time(nullptr)) {}

    int getButtonId() const { return button_id; }
    SmileyType getType() const { return type; }
    int getLightId() const { return light_id; }
    time_t getTimestamp() const { return timestamp; }
    void setTimestamp(struct tm* new_timestamp) { timestamp = mktime(new_timestamp); }
    void setType(SmileyType new_type) { type = new_type; }
private:
    int button_id;
    SmileyType type;
    int light_id;
    time_t timestamp;
};

enum SmileyType {
    SMILEY_TYPE_NONE = 0,
    SMILEY_TYPE_ANGRY,
    SMILEY_TYPE_SAD,
    SMILEY_TYPE_MEH,
    SMILEY_TYPE_HAPPY
};