#pragma once

#include "esphome.h"

class HC8CO2Sensor : public PollingComponent, public UARTDevice {
 public:
  HC8CO2Sensor(UARTComponent *parent) : UARTDevice(parent), PollingComponent(60000) {}

  Sensor *co2_sensor = new Sensor();
  TextSensor *status_text = new TextSensor();

  void setup() override;
  void update() override;

 private:
  uint16_t calculate_checksum(const uint8_t *data, size_t length);
};

