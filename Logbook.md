# Logbook

## Day 1:

### Setting up project

Discussed design principles, project structure , role allocation and broke down tasks.

We set up a Github Project as our management tool, created the repository and added the broken down tasks to the board that were then allocated in the team.

Development environement, required libraries, interfaces/types and physical product was designed and hardware was initially tested to ensure expected behaviour

### Development start

We added our overall structure to the project - I.e interfaces and helper methods.

Added some simple functionality to expand upon for the required features, we basically
wanted to register the buttons based on our interface and relevant values to test that each button press would light the correct diode, register the correct time in the correct format all with the correct value corresponding to the buttons id. Our primary focus were expand- and scalability hence the dynamic loading that allowed us to add and adjust the amount of hardware on the board. This way we could check one button and know that future issues with registration would be due to faulty hardware.  

```cpp
public:
    Smiley() {}
    Smiley(int button_id, SmileyType type, int light_id)
        : button_id(button_id), type(type), light_id(light_id) {}

    int getButtonId() const { return button_id; }
    SmileyType getType() const { return type; }
    int getLightId() const { return light_id; }
    struct tm* getTimestamp() const { return timestamp; }
    void setTimestamp(struct tm* new_timestamp) { timestamp = new_timestamp; }

private:
    int button_id;
    SmileyType type;
    int light_id;
    struct tm* timestamp;
};

```

Read documentation for required features and started implementation of deep-sleep, WiFi and NTP.
```cpp
#pragma once
class APService
{
public:
    static void setup();
    static void Disconnect();
    static bool isConnected();
};

```
```cpp
class NTPService
{
public:
    static void setup();
    static struct tm* getTime();
};
```

Updated the project board, with tasks and allocated focus areas to read up on for next development day.

## Day 2:

Started work on deep-sleep implementation and tested different optimization approaches, experimented with EzButton, but ended up using more simple behaviour for the registration of button.

Deep-sleep got implemented with a bitmask based on our getButtonId method that takes our defined Buttons registered pins integer, the integer is itterated over and registered as a pin that allows for wake up.

```cpp
  // registers pins used for waking up program
  uint64_t wakeupPins = 0;
  for (Smiley smiley : smiley) {
    wakeupPins |= (1ULL << smiley.getButtonId());
  }
```

We set a cause of wakeup to be EXT1, initially we set the type to be GPIO

Though after testing the type that the wakeup returned was == 3 corrosponding to the type of EXT1.

After a longer testing and debugging phase trying to optimize program execution performance, simplified our code and added an "END" state to our SmileyType enum, which would be reliable in the sense that every type should correspond with a button, which essentially did that we wouldn't calculate the size of our array but relied on the assigned types.   
We settled on a simple approach for button registration, implemented a simple custom debounce and proceeded with tests for ensuring program consistency and reverted some of the dynamic code functionality.

We also tried experimenting with pointers with our ezButton library, but also ended up backtracking for a clearer and more simple approach.
```cpp
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
```

We added safe guards for our AP service such that we only create a new connection when one isn't present. 
```cpp
  if (!APService::isConnected())
  {
    APService::setup();
    NTPService::setup();
  }
```


Logbook was officially added to the project as [Logfile.md](http://Logfile.md)
