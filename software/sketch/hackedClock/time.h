#ifndef TIME_H
#define TIME_H

#include <TimeLib.h>    // https://www.pjrc.com/teensy/td_libs_Time.html
#include <Timezone.h>   // https://github.com/JChristensen/Timezone
#include <DS3231RTC.h>  // Mine


// US Eastern Time Zone (New York, Detroit, Toronto, Montreal, etc...)
TimeChangeRule myDST = {"EDT", Second, Sun, Mar, 2, -240};    // Daylight time = UTC - 4 hours
TimeChangeRule mySTD = {"EST", First, Sun, Nov, 2, -300};     // Standard time = UTC - 5 hours
TimeChangeRule *tcr;        // Pointer to the time change rule, use to get TZ abbrev
Timezone myTZ(myDST, mySTD);


#define MINUTES_TO_MS 60000L

#define DEFAULT_TIME  1357041600 // Jan 1 2013
#define RTC_UPDATE_INTERVAL 55 // in seconds

uint8_t timeHours = 6;
uint8_t timeMinutes = 45;

#define SLEEP_DEFAULT_MIN  3
int8_t sleepMinutes = -1;   // -1 = disabled
uint8_t sleepSeconds = 0;


#define SNOOZE_DELAY   2  // in minutes


// Alarm states
#define AL_DISABLED      0
#define AL_ENABLED       1
#define AL_WAS_TRIG      2
#define AL_TRIGGERED     3
#define AL_SNOOZED       4

int8_t alarm1Status = -1;
uint8_t alarm1Hours = 19;
uint8_t alarm1Minutes = 12;
bool alarm1NeedsUpdate = false;
uint8_t alarm1SnoozeMin = 0;
uint8_t alarm1SnoozeSec = 0;

int8_t alarm2Status = -1;
uint8_t alarm2Hours = 19;
uint8_t alarm2Minutes = 15;
bool alarm2NeedsUpdate = false;
uint8_t alarm2SnoozeMin = 0;
uint8_t alarm2SnoozeSec = 0;

// debugging
bool forceNTPFail = false;
bool forceBadRTC = false;
bool serialClockEnabled = false;

#endif
