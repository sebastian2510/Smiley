#pragma once
struct Debounce {
    int button_id;
    unsigned long last_time;
    Debounce(int id, unsigned long time) : button_id(id), last_time(time) {}

    bool isDebounced(int id, unsigned long current_time) {
        if (id != button_id) {
            return false; 
        }

        if (current_time - last_time > 50) {
            last_time = current_time;
            return true;
        }
        return false;
    }
};