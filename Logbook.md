# Logbook

## Day 1:

### Setting up project

Discussed design principles, project structure , role allocation and broke down tasks.

We set up a Github Project as our management tool, created the repository and added the broken down tasks to the board that were then allocated in the team.

Development environement, required libraries, interfaces/types and physical product was designed and hardware was initially tested to ensure expected behaviour

### Development start

We added our overall structure to the project - I.e interfaces and helper methods.

Added some simple functionality to expand upon for the required features, we basically
wanted to register the buttons based on our interface and relevant values to test that each button press would light the correct diode, register the correct time in the correct format all with the correct value corrosponding to the buttons id.

Read documentation for required features and started implementation of deep-sleep and NTP

Updated the project board, with tasks and allocated focus areas to read up on for next development day.

## Day 2:

Started work on deep-sleep implementation and tested different optimization approaches, experimented with EzButton, but ended up using more simple behaviour for the registration of button.

Deep-sleep got implemented with a bitmask based on our getButtonId method that takes our defined Buttons registered pins integer, the integer is itterated over and registered as a pin that allows for wake up.

```
  // registers pins used for waking up program
  uint64_t wakeupPins = 0;
  for (Smiley smiley : smiley) {
    wakeupPins |= (1ULL << smiley.getButtonId());
  }
```

We set a cause of wakeup to be EXT1, initially we set the type to be GPIO

Though after testing the type that the wakeup returned was == 3 corrosponding to the type of EXT1.

After a longer testing and debugging phase trying to optimize program execution performance, we settled on a simple approach for button registration, implemented a simple custom debounce and proceeded with tests for ensuring program consistency.

We also tried experimenting with pointers with our ezButton library, but also ended up backtracking for a clearer and more simple approach.

Logbook was officially added to the project as [Logfile.md](http://Logfile.md)
