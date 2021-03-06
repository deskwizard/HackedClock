#ifndef KEYS_H
#define KEYS_H


// Debug LED
#define LED_PIN 0 // on MCP23008
#define FLASH_DELAY 250

//#define INT_DEBUG


// all addr low = 0x20 , all high = 0x27
#define MCP_ADDR      0x27

#define MCP_INT_PIN   18


#define KEY_STATE_UP 0
#define KEY_STATE_DOWN 1
#define KEY_TIMEOUT 750


#define KEY_PWR     1     // Also alarm off
#define KEY_V_DN    2     // Also alarm 1 toggle
#define KEY_V_UP    3     // Also alarm 2 toggle
#define KEY_DIM     4     // also sleep and snooze
#define KEY_F_DN    5     // also hour
#define KEY_F_UP    7     // also minutes
#define KEY_CLK     6     // also memory (Radio Station eeprom save ??)
   
#define KEY_COUNT   7
#define FIRST_KEY   KEY_PWR
#define LAST_KEY    KEY_CLK

#endif
