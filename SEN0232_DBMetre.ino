#include <Arduino.h>

const int SEN0232_PIN = 33;
const int sensitivity = 50;

float sound_dB = 0, sound_voltage = 0;

// To store sound reading data
unsigned long lastSoundRead = 0;

// How fast you would want your sound readings to be taken
const unsigned long soundInterval = 10;

void setup() {
  Serial.begin(115200);

  analogReadResolution(12);
  analogSetPinAttenuation(SEN0232_PIN, ADC_11db);
}



void loop() {
  unsigned long currentMillis = millis();

  // Take a sound reading every `soundInterval` milliseconds (non-blocking)
  if (currentMillis - lastSoundRead >= soundInterval) {
    lastSoundRead = currentMillis;

    readSoundSensor();
    printCSV();
  }
}

// Uses DFRobot Formula (dB = voltage * sensitivity) to convert voltage to dB
void readSoundSensor() {
  uint32_t voltage_mV = analogReadMilliVolts(SEN0232_PIN);

  sound_voltage = voltage_mV / 1000.0;

  sound_dB = sound_voltage * sensitivity;

  sound_dB = constrain(sound_dB, 30.0, 130.0);
}


// print reading function in CSV format (one value per line).
void printCSV() {
  Serial.println(sound_dB, 1);
}
