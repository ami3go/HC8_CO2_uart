#include "hc8_co2_uart.h"

void HC8CO2Sensor::setup() {
  this->status_text->publish_state("Initializing...");
}

void HC8CO2Sensor::update() {
  static const uint8_t QUERY_CMD[] = {0x64, 0x69, 0x03, 0x5E, 0x4E};
  uint8_t response[14];

  this->write_array(QUERY_CMD, sizeof(QUERY_CMD));
  delay(100);  // Use non-blocking methods in final implementation

  if (this->available() >= 14) {
    this->read_array(response, 14);

    if (response[0] == 0x64 && response[1] == 0x69) {
      uint16_t checksum = calculate_checksum(response, 12);
      uint16_t received_checksum = (response[13] << 8) | response[12];

      if (checksum == received_checksum) {
        uint16_t co2_ppm = (response[4] << 8) | response[5];
        this->co2_sensor->publish_state(co2_ppm);
        this->status_text->publish_state("Measurement OK");
      } else {
        this->status_text->publish_state("Checksum Error");
      }
    } else {
      this->status_text->publish_state("Invalid Response");
    }
  } else {
    this->status_text->publish_state("No Response");
  }
}

uint16_t HC8CO2Sensor::calculate_checksum(const uint8_t *data, size_t length) {
  uint16_t checksum = 0;
  for (size_t i = 0; i < length; i++) {
    checksum += data[i];
  }
  return checksum;
}

