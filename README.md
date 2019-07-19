# MX5-Arduino-Speed

## Target Hardware

Arduino ATMega328p

2.42 Inch SS1309 128x64 Monocrhome OLED

5v Beeper

5v Speed sensor (#DSSA from www.carbuildersolutions.com)

## Pinout

OLED_MOSI   9

OLED_CLK   10

OLED_DC    11

OLED_CS    12

OLED_RESET 13

Beeper 2 (and to GND)

Speed sesor 4 (and 5v, GND)

## Configuration commands (via USB Serial 115200)

ODO - Press return and then enter new odometer reading

PPM - Press return and enter pulses per half mile (use CAL mode in preference)

CAL - Enter calibration mode (see below)

RUN - Exit calibration mode

## Calibration mode

In calibration mode it starts counting pulses immediately. Calibration should be done over a measured half a mile. Press enter when starting the half mile, and again at the end. The number of pulses will be displayed on the screen. To write this to EEPROM and return to normal mode type 'RUN'. If the data is not suitable (missed marker etc) then just repeat the measurement.

