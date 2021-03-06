#ifndef DEFINES_H
#define DEFINES_H

#define BATT_OVERRIDE // intensity default = max
//#define BATT_OVERRIDE2  // blanking display override

#define TEST_LED_PIN 15

#define SCL_PIN 16
#define SDA_PIN 17

bool audioEnabled = false;


#define EEPROM_SIZE               40    // EEPROM reserved size (ESP32)

#define EE_ADDR_INTENSITY         0

#define EE_ADDR_VOL               5

#define EE_ADDR_RADIO_LOW         10
#define EE_ADDR_RADIO_HIGH        EE_ADDR_RADIO_LOW +1

#define EE_ADDR_AL1_ENABLED       20
#define EE_ADDR_AL1_HR            EE_ADDR_AL1_ENABLED +1
#define EE_ADDR_AL1_MIN           EE_ADDR_AL1_ENABLED +2

#define EE_ADDR_AL2_ENABLED       30
#define EE_ADDR_AL2_HR            EE_ADDR_AL2_ENABLED +1
#define EE_ADDR_AL2_MIN           EE_ADDR_AL2_ENABLED +2


#endif
