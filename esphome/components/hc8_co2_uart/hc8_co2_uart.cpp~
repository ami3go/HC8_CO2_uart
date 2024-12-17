#include "hc8_co2_uart.h"

namespace esphome {
namespace hc8_co2_uart {

void HC8CO2UART::setup() {
  ESP_LOGCONFIG(TAG, "Setting up HC8 CO2 UART...");
}

void HC8CO2UART::update() {
/**
https://hackaday.com/2022/08/31/mh-z19-like-ndir-co2-sensor-hc8-found-and-explored/
The output format is 16BYTE.
Data header: BYTE0 = 0X42; BYTE1=4D
BYTE6 data is high, BYTE7 data is low, indicating CO2 concentration.
BYTE15, data checksum. BYTE15= BYTE0+BYTE1+…….+BYTE13;

Example: 42 4D 0C 51 09 A2 07 2B 01 35 05 81 20 08 20 AD;
CO2 concentration = BYTE6 X 256 + BYTE7 = 07X256 + 2B = 1853;
**/	
	
  ESP_LOGD(TAG, "Reading CO2 concentration...");
  uint8_t command[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
  this->write_array(command, sizeof(command));
  delay(10);

  uint8_t response[9];
  if (this->available() >= 9) {
    this->read_array(response, sizeof(response));
    if (validate_checksum_(response)) {
      uint16_t co2 = (response[2] << 8) | response[3];
      ESP_LOGD(TAG, "CO2 Concentration: %d ppm", co2);
      if (this->co2_sensor_ != nullptr) {
        this->co2_sensor_->publish_state(co2);
      }
    } else {
      ESP_LOGW(TAG, "Checksum validation failed for HC8 sensor data.");
    }
  } else {
    ESP_LOGW(TAG, "No valid data received from HC8 sensor.");
  }
}

void HC8CO2UART::dump_config() {
  ESP_LOGCONFIG(TAG, "HC8 CO2 UART:");
  LOG_SENSOR("  ", "CO2 Concentration", this->co2_sensor_);
}

bool HC8CO2UART::validate_checksum_(const uint8_t *data) {
  uint8_t checksum = 0;
  for (int i = 1; i < 8; i++) {
    checksum += data[i];
  }
  checksum = 0xFF - checksum + 1;
  return checksum == data[8];
}

}  // namespace hc8_co2_uart
}  // namespace esphome



