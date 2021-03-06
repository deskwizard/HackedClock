#ifndef MCP_DISPLAY_H
#define MCP_DISPLAY_H

#include "Arduino.h"


#define DISP_ADDR_LOW     0x25
#define DISP_ADDR_HIGH    0x20
#define SCL_PIN           16
#define SDA_PIN           17

#define INTENSITY_PIN     21
#define DISP_INT_CHAN     0
#define DISP_PWM_FREQ     50000
#define DISP_PWM_BITS     13

#define MIN_INTENSITY     1
#define MAX_INTENSITY     15
#define DEF_INTENSITY     MAX_INTENSITY

// Indicators IDs
// If declared in the right order, digit number can be figured out easily, > 2 always digit 3
#define IND_FM        0
#define IND_AL2       1
#define IND_DOT       2
#define IND_TOP_COL   3
#define IND_BOT_COL   4
#define IND_AL1       5
#define IND_SLEEP     6
#define IND_PM        7


class MCP_DISPLAY {

  public:
    MCP_DISPLAY();

    // For testing
    void updateOne(uint8_t digit);
    void updateAll();

    void test();
    
    void setup();
    
    void setDigit(uint8_t digit, uint8_t index);
    void setChar(uint8_t digit, uint8_t character);
    void shutdown(bool state);
    void clearDisplay();
    void setIntensity(uint8_t array_index);
    void setIndicator(uint8_t ind_id, bool state);
    void clearIndicators();
    void clearSomeIndicators();


    void setAllOn();

    void testDispSeg();
    void test_seq();
    void test_indicators();

  private:
    uint8_t digitShadow[4] = { 0x00 };

    // By LUT table index
    uint8_t currentIntensity = DEF_INTENSITY;

    const uint16_t intensity_lut[MAX_INTENSITY + 1] = {2, 3, 4, 5, 7, 670, 888, 1106, 1465, 1825, 2417, 3010, 3988, 4966, 6578, 8192 };

    // Numbers from 0 to 15 mapped to their binary values (A is LSB)
    const uint8_t num_map[16] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
                                 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111,
                                 0b01110111, 0b01111100, 0b01011000, 0b01011110, 0b01111001, 0b01110001
                                };


    //    void updateOne();
    //    void updateAll();
};


#endif
