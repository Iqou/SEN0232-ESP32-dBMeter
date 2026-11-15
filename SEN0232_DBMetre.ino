#include <Arduino.h>

const int SEN0232_PIN = 33;
const int sensitivity = 50;

float sound_dB = 0, sound_voltage = 0;

unsigned long lastSoundRead = 0;

const unsigned long soundInterval = 10;

void setup() {
  Serial.begin(115200);

  analogReadResolution(12);
  analogSetPinAttenuation(SEN0232_PIN, ADC_11db);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastSoundRead >= soundInterval) {
    lastSoundRead = currentMillis;

    readSoundSensor();
    printCSV();
  }
}

void readSoundSensor() {
  uint32_t voltage_mV = analogReadMilliVolts(SEN0232_PIN);

  sound_voltage = voltage_mV / 1000.0;

  sound_dB = sound_voltage * sensitivity;

  sound_dB = constrain(sound_dB, 30.0, 130.0);
}

void printCSV() {
  Serial.println(sound_dB, 1);
}
