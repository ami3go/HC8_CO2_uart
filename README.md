# HC8_CO2
Fork from  MH-Z19 https://github.com/nara256/mhz19_uart and work for get HC8 CO2 senspor supported by ESPHOME

Status: 

16.12.24 - forked project. 

# Credits and license  
License MIT

# How to use

* Include this library to your Arduino IDE.
* HC8 is pin to pin compatible, but protocol is different. 
* Wiring MH-Z19 sensor to your Arduino or ESP-WROOM-02/32(ESP8266/ESP32).

    MH-Z19 Vout to Arduino Vout(5V)  
    MH-Z19 GND  to Arduino GND  
    MH-Z19 Tx   to Arduino Digital Pin (Serial Rx pin)  
    MH-Z19 Rx   to Arduino Digital Pin (Serial Tx pin)  
    other MH-Z19 pins are not used.  

* Read sample source code. It's very simple !

# caution

* MH-Z19 is supporting PWM , but this library is supporting only serial connection. 
* this library is testing only ESP-WROOM-02/32(ESP8266/ESP32) boards. if you can't execute this library on your arduino (or clone) boards, please contact me.

# MHZ19_uart library function

## Constractor

* MHZ19_uart  
  normal constractor. if you use this constractor, you must execute begin() function after this constractor execute.

* MHZ19_uart(int rx, int tx)  
  setting rx and tx pin, and initialize Serial.

## public function

* void begin(int rx, int tx)  
  setting rx and tx pin, and initialize Serial.

* void setHardwareSerialNo(int serialNo)  
  setting hardware serial no. # You can use this function only ESP32.
  
* void setAutoCalibration(bool autocalib)  
  MH-Z19 has automatic calibration procedure. the MH-Z19 executing automatic calibration, its do zero point(stable gas environment (400ppm)) judgement.
  The automatic calibration cycle is every 24 hours after powered on.  
  If you use this sensor in door, you execute `setAutoCalibration(false)`.

* void calibrateZero()  
  execute zero point calibration. 
  if you want to execute zero point calibration, the MH-Z19 sensor must work in stable gas environment (400ppm) for over 20 minutes and you execute this function.

* void calibrateSpan(int ppm)  
  execute span point calibration.
  if you want to execute span point calibration, the MH-Z19 sensor must work in between 1000 to 2000ppm level co2 for over 20 minutes and you execute this function.
  
* int getCO2PPM()  
  get co2 ppm.
  
* int getTemperature()  
  get temperature (MH-Z19 hidden function?  this function is not support.)

# link
# there is no much information about it, but here is what is already known 
* hackaday.com
   
    https://hackaday.com/2022/08/31/mh-z19-like-ndir-co2-sensor-hc8-found-and-explored/

* spezifisch.codeberg.page
   
  https://spezifisch.codeberg.page/posts/2022-08-23/co2-sensor-reverse-engineering/

* reddit.com
  
  https://www.reddit.com/r/hackaday/comments/x2ohlu/mhz19like_ndir_co2_sensor_hc8_found_and_explored/

* github
  
  https://github.com/esphome/feature-requests/issues/2550

  
# history
* ver. 0.1: closed version.
* ver. 0.2: first release version.
* ver. 0.3: support ESP-WROOM-32(ESP32), Change library name. (MHZ19_Serial -> MHZ19_uart)
* ver. 0.31: Operation check on MH-Z19C, Delete functions getStatus() and isWarming(), And refactor details.

