// /*----------------------------------------------------------
//     MH-Z19 CO2 sensor  SAMPLE
//   ----------------------------------------------------------*/

// #include "../../src/HC8_CO2_uart.h"

// const int rx_pin = 16; //Serial rx pin no
// const int tx_pin = 17; //Serial tx pin no

// HC8_CO2_uart hc8_co2;

// /*----------------------------------------------------------
//     MH-Z19 CO2 sensor  setup
//   ----------------------------------------------------------*/
// void setup()
// {
//   Serial.begin(9600);
//   hc8_co2.begin(rx_pin, tx_pin);
//   hc8_co2.setAutoCalibration(false);

//   Serial.println("MH-Z19 is warming up now.");
//   delay(10 * 1000); //
// }

// /*----------------------------------------------------------
//     MH-Z19 CO2 sensor  loop
//   ----------------------------------------------------------*/
// void loop()
// {
//   int co2ppm = hc8_co2.getCO2PPM();
//   int temp = hc8_co2.getTemperature();

//   Serial.print("co2: ");
//   Serial.println(co2ppm);
//   Serial.print("temp: ");
//   Serial.println(temp);

//   delay(5000);
// }



#include "../../src/HC8_CO2_uart.h"

HC8_CO2_uart co2Sensor;

void setup() {
    Serial.begin(9600);

    // ESP32 example (optional):
    // co2Sensor.setHardwareSerialNo(1);

    co2Sensor.begin(16, 17); // Use appropriate RX, TX pins
    // co2Sensor.setAutoCalibration(false);
}

void loop() {
    int co2 = co2Sensor.getCO2PPM();
    int temp = co2Sensor.getTemperature();

    Serial.print("CO2: ");
    Serial.print(co2);
    Serial.print(" ppm, Temp: ");
    Serial.print(temp);
    Serial.println(" °C");

    delay(1000);
}