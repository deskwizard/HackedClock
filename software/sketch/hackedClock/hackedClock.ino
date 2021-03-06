/*

  Currently hunting:


*/

// **** WARNING --- Soft reset by serial will make the RTC fails on boot ****

#include "defines.h"
#include "keys.h"
#include "time.h"
#include "display.h"
#include "power.h"
#include <WiFi.h>
#include "EEPROM.h"


// On Linux, you can use "date +T%s\n > /dev/ttyUSB0" (for example) for UTC time zone
// fake in the past date: T1407788400\n (PM) @ 4:20
// fake in the past date: T1407745200\n (AM) @ 4:20
// before midnight: T1628683170\n
// before midnight: T1628639970\n
// before noon:     T1628679570\n


// For serial testing eeprom
extern int8_t displayIntensity;


void setup() {

  setCpuFrequencyMhz(80);

  Serial.begin(115200);
  delay(5000);
  Serial.println();
  Serial.println();
  Serial.println("Hello");


  pinMode(TEST_LED_PIN, OUTPUT);

  EEPROM.begin(EEPROM_SIZE);

  Wire.begin(SCL_PIN, SDA_PIN); // Required to work properly. (Else RTC.set() won't work with NTP, go figure.)
  // It will fail without that line, but will show succeeed even though it didn't with it in... ??

  setupTime(); // Needs to be RIGHT after Wire.begin()

  setupDisplay(); // Needs to be run before anything else tries to use it.

  setupPower();

  setupKeys();
  setupAlarms(); // Needs to be run after setupTime, we need to know if time is valid.
  setupAudio();
  setupWiFi();

} // setup


void loop() {

  handlePower();

  handleWiFi();
  handleNTP();

  checkKeys();
  handleSerial();
  handleDisplay();
  handleAlarms();
  handleSleep();



  static bool ledState = false;
  uint32_t currentMillis = millis();
  static uint32_t previousMillis = currentMillis;
  if ((uint32_t)(currentMillis - previousMillis) >= FLASH_DELAY) {
    ledState = !ledState;
    writeLed(ledState);
    digitalWrite(TEST_LED_PIN, ledState);
    previousMillis = currentMillis;
  }

} // loop




void handleSerial() {


  if (Serial.available()) {

    unsigned char c = Serial.read();
    int readValue;

    switch (c) {
      case '8':
        displayShutdown(true);
        break;
      case '9':
        displayShutdown(false);
        break;
          
      case 'T':   // Set RTC time using serial (UTC)
        processSyncMessage();
        break;

      case '=':
        saveAlarm1Time();
        break;
      case '-':
        restoreAlarms();
        break;

      case 'c':
        clearEEPROM();
        break;
      case 'R':
        readEEPROM();
        break;
      case 'r':
        printIntensityEE();
        break;
      case '#':
        saveIntensity(displayIntensity);
        break;

      case 'j':
        sleepMinutes = 3;
        Serial.print(" --- Sleeping for ");
        Serial.print(sleepMinutes);
        Serial.println(" min");
        updateDisplay(DISP_SLEEP);
        displayTimeout();
        break;

      case 'y':
        alarm1Status = AL_TRIGGERED;
        Serial.println("Alarm 1 triggered");
        break;
      case 'l':
        alarm2Status = AL_TRIGGERED;
        Serial.println("Alarm 2 triggered");
        break;
      case 'q':
        sleepMinutes = -1;
        break;
      case 'Q':
        sleepMinutes = SLEEP_DEFAULT_MIN;
        break;
      case 'w':
        Serial.print("Snooze AL1 - ");
        alarm1Status = AL_SNOOZED;
        alarm1SnoozeMin = minute() + SNOOZE_DELAY;
        alarm1SnoozeSec = second();
        disableAudio();
        if (alarm1SnoozeMin >= 60) {
          alarm1SnoozeMin = alarm1SnoozeMin - 60;
        }
        Serial.print("Snooze min: ");
        Serial.println(alarm1SnoozeMin);
        Serial.print("Snooze sec: ");
        Serial.println(alarm1SnoozeSec);

        break;



      case 'a':
        disableAudio();
        break;
      case 'A':
        enableAudio();
        break;
      case 'p':
        Serial.print("P: ");
        printRadio();
        break;
      case 'u':
        tuneDown();
        break;
      case 'd':
        tuneUp();
        break;
      case 's':
        seekDown();
        break;
      case 'S':
        seekUp();
        break;

      case 'v':
        volumeDown();
        break;
      case 'V':
        volumeUp();
        break;

      case '*':
        serialClockEnabled = !serialClockEnabled;
        break;


      case 'i':
        readValue = Serial.parseInt();
        displaySetIntensity(readValue);
        break;
      case 'b':
        //readValue = Serial.parseInt();
        saveRadioStation();
        break;

      case '/':
        RTC.set(0);
        ESP.restart();
        break;
    }
  }
}


void processSyncMessage() {

  uint32_t pctime = Serial.parseInt();

  if (pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
    Serial.println(" *** Serial time and RTC update ***");
    setTime(pctime + 18000); // Sync Arduino clock to the time received on the serial port
    RTC.set(pctime + 18000);
    digitalClockDisplay();  // workaround TODO: fix
  }

}



void readEEPROM() {

  Serial.println("Reading EEPROM...");

  for (uint8_t x = 0; x < EEPROM_SIZE; x++) {
    Serial.print(x);
    Serial.print(": B: ");
    Serial.println(EEPROM.read(x));
  }

  Serial.println("Done");
  Serial.println();

}


void clearEEPROM() {

  Serial.println("Wiping EEPROM...");

  for (uint8_t x = 0; x < EEPROM_SIZE; x++) {

    //    Serial.print(x);
    //    Serial.print(": B: ");
    //    Serial.print(EEPROM.read(x));

    EEPROM.write(x, 0xFF);
    EEPROM.commit();

    Serial.print("RB: ");
    Serial.print(x);
    Serial.print(": ");
    Serial.println(EEPROM.read(x));
  }

  Serial.println("Done");
  Serial.println();

}
