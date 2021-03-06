#ifndef DISPLAY_H
#define DISPLAY_H

#define DIGIT_COUNT 4   // Either 4 or 6

#define NTP_Digit        3
#define AM_PM_Digit      0


// Might have side effects (trying to get an easy if statement for both commas lit)
#define DISP_TIME        0
#define DISP_AL1         1
#define DISP_AL2         2
#define DISP_VOL         3
#define DISP_SLEEP       4

#define DISP_FREQ        5

#define DISP_AL1_TXT     6
#define DISP_AL2_TXT     7
#define DISP_OFF_TXT     8

#define DISP_BLANK       9




#define DISP_TIMEOUT 1000

#define DOT_FLASH_DELAY 500

#define MAX_INTENSITY       15
#define MIN_INTENSITY        1

#if defined BATT_OVERRIDE
#define DEFAULT_INTENSITY    7
#define BATT_PWR_INTENSITY   3
#else
#define DEFAULT_INTENSITY    MAX_INTENSITY
#define BATT_PWR_INTENSITY   MAX_INTENSITY
#endif

#endif
