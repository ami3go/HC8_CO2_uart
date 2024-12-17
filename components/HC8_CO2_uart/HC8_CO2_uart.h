#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace hc8_co2_uart {

class HC8CO2UART : public PollingComponent, public uart::UARTDevice {
 public:
  HC8CO2UART() : PollingComponent(60000) {}  // Poll every 60 seconds

  void set_co2_sensor(sensor::Sensor *co2_sensor) { co2_sensor_ = co2_sensor; }
//  void loop() override;	
  void setup() override;
  void update() override;
  void dump_config() override;

 protected:
  sensor::Sensor *co2_sensor_{nullptr};

  bool validate_checksum_(const uint8_t *data);
};

}  // namespace hc8_co2_uart
}  // namespace esphome
