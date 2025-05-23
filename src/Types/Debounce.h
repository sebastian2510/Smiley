#pragma once
struct Debounce {
    int button_id;
    unsigned long last_time;
    Debounce(int id, unsigned long time) : button_id(id), last_time(time) {}
    
    /**
     * @brief Checks if the button with the given ID is debounced based on the current time.
     *
     * This function compares the provided button ID with the stored button ID. If they do not match,
     * it returns false. If they match, it updates the button ID and the last recorded time, then checks
     * if the elapsed time since the last press is within the debounce threshold (50 milliseconds).
     *
     * @param id The identifier of the button to check.
     * @param current_time The current time in milliseconds.
     * @return true if the button press is within the debounce period, false otherwise.
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