/*
  HC8_CO2_uart.cpp - MH-Z19 CO2 sensor library for ESP-WROOM-02/32(ESP8266/ESP32) or Arduino
  version 0.3
  
  License MIT
*/

#include "HC8_CO2_uart.h"
#include "Arduino.h"

#define WAIT_READ_TIMES 100
#define WAIT_READ_DELAY 10

// public
HC8_CO2_uart::HC8_CO2_uart()
{
}
HC8_CO2_uart::HC8_CO2_uart(int rx, int tx)
{
	begin(rx, tx);
}

HC8_CO2_uart::~HC8_CO2_uart()
{
}

void HC8_CO2_uart::begin(int rx, int tx)
{
	_rx_pin = rx;
	_tx_pin = tx;
}

void HC8_CO2_uart::setAutoCalibration(boolean autocalib)
{
	writeCommand(autocalib ? autocalib_on : autocalib_off);
}

void HC8_CO2_uart::calibrateZero()
{
	writeCommand(zerocalib);
}

void HC8_CO2_uart::calibrateSpan(int ppm)
{
	if (ppm < 1000)
		return;

	uint8_t com[HC8_CO2_uart::REQUEST_CNT];
	for (int i = 0; i < HC8_CO2_uart::REQUEST_CNT; i++)
	{
		com[i] = spancalib[i];
	}
	com[3] = (uint8_t)(ppm / 256);
	com[4] = (uint8_t)(ppm % 256);
	writeCommand(com);
}

int HC8_CO2_uart::getCO2PPM()
{
	readSerialData();
	return _co2;
}

int HC8_CO2_uart::getTemperature()
{
	readSerialData();
	return _co2temp;
}

#ifdef ARDUINO_ARCH_ESP32
void HC8_CO2_uart::setHardwareSerialNo(int serialNo)
{
	_serialNo = serialNo;
}
#endif

//protected
void HC8_CO2_uart::writeCommand(uint8_t cmd[])
{
	writeCommand(cmd, NULL);
}

void HC8_CO2_uart::writeCommand(uint8_t cmd[], uint8_t *response)
{
#ifdef ARDUINO_ARCH_ESP32
	HardwareSerial hserial(_serialNo);
	hserial.begin(9600, SERIAL_8N1, _rx_pin, _tx_pin);
#else
	SoftwareSerial hserial(_rx_pin, _tx_pin);
	hserial.begin(9600);
#endif
	hserial.write(cmd, REQUEST_CNT);
	hserial.write(HC8_CO2_checksum(cmd));
	hserial.flush();

	if (response != NULL)
	{
		int i = 0;
		while (hserial.available() <= 0)
		{
			if (++i > WAIT_READ_TIMES)
			{
				Serial.println("error: can't get MH-Z19 response.");
				return;
			}
			yield();
			delay(WAIT_READ_DELAY);
		}
		hserial.readBytes(response, HC8_CO2_uart::RESPONSE_CNT);
	}
}

//private
void HC8_CO2_uart::readSerialData()
{
	uint8_t buf[HC8_CO2_uart::RESPONSE_CNT];
	for (int i = 0; i < HC8_CO2_uart::RESPONSE_CNT; i++)
	{
		buf[i] = 0x0;
	}

	writeCommand(getppm, buf);

	// parse
	if (buf[0] == 0xff && buf[1] == 0x86 && HC8_CO2_checksum(buf) == buf[HC8_CO2_uart::RESPONSE_CNT - 1])
	{
		_co2 = buf[2] * 256 + buf[3];
		_co2temp = buf[4] - 40;
		_co2status = buf[5];
	}
	else
	{
		_co2 = _co2temp = _co2status = -1;
	}
}

uint8_t HC8_CO2_uart::HC8_CO2_checksum(uint8_t com[])
{
	uint8_t sum = 0x00;
	for (int i = 1; i < HC8_CO2_uart::REQUEST_CNT; i++)
	{
		sum += com[i];
	}
	sum = 0xff - sum + 0x01;
	return sum;
}

//deprecated
int HC8_CO2_uart::getPPM()
{
	return getCO2PPM();
}
//deprecated
int HC8_CO2_uart::getStatus()
{
	return 0;
}
//deprecated
boolean HC8_CO2_uart::isWarming()
{
	delay(10 * 1000);
	return true;
}
