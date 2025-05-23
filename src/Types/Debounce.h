#pragma once
struct Debounce {
    int button_id;
    unsigned long last_time;
    Debounce(int id, unsigned long time) : button_id(id), last_time(time) {}
    

    /**
     * @brief Checks if the button with the given ID is experiencing a debounce event.
     *
     * This function determines whether the button press event for the specified ID
     * should be considered as "bounced" based on the elapsed time since the last event.
     * It updates the internal state with the current button ID and timestamp.
     *
     * @param id The identifier of the button to check.
     * @param current_time The current time in milliseconds.
     * @return true if the button event is within the debounce threshold (<= 50 ms), false otherwise.
     */
    bool isBounced(int id, unsigned long current_time) {
        if (id != button_id) {
            return false; 
        }

        button_id = id;
        last_time = millis();
        return current_time - last_time <= 50;
    }
};