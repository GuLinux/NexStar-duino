#include "battery.h"

// Voltmeter: AnalogPin 10, R1=7440, R2=8180

#define BATTERY_PIN 10
#define READ_EVERY_MILLIS 1000

#define MAX_VOLTS 6000
#define MAX_VALUE 4096

#define MAX_VOLTS_DIVIDER 3142


Battery::Battery() : Singleton<Battery>(this) {
}

void Battery::setup() {
  pinMode(BATTERY_PIN, INPUT_ANALOG);
}

uint16_t Battery::read() {
  if(last_reading == 0 || millis() - last_reading_time > READ_EVERY_MILLIS) {
    last_reading_time = millis();
    last_reading = analogRead(BATTERY_PIN);
  }
  return last_reading;
}

uint16_t Battery::millivolts() {
  return static_cast<uint16_t>(static_cast<uint32_t>(read()) * MAX_VOLTS / MAX_VALUE);
}

