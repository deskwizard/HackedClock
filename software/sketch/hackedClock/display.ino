
/*

  TODO:
      - have an indication on WiFi failed and NTP failed


*/

#include "MCP_Display.h"
MCP_DISPLAY display;

uint32_t displayTimeoutMillis = 0;
uint8_t lastDisplayMode = DISP_TIME;


int8_t displayIntensity = -1;
int8_t savedDisplayIntensity = -1;


extern uint8_t volume;
extern bool NTPState;         // Result of the last NTP update (Succeed (true) or fail (false))


void setupDisplay() {

  display.setup();

  // HERE set saved intensity
  displayIntensity = restoreIntensityEE();
  savedDisplayIntensity = displayIntensity;
  display.setIntensity(displayIntensity);   /************ HERE ************/

  displayDashes();                // Self-explanatory
  delay(3000);

  if (timeStatus() != timeNotSet) {
    updateDisplay(DISP_TIME);
  }
  else {
    displayDashes();                // Self-explanatory
  }
} // setup


void displayShutdown(bool shutdown_val) {  // TODO irrelevant?
  display.shutdown(shutdown_val);
  Serial.print("Display shutdown: ");
  Serial.println(shutdown_val);
}



void displayTimeout() {
  displayTimeoutMillis = millis() + DISP_TIMEOUT;
}


void handleDisplay() {


  static uint8_t previousMinute = 0;
  if (timeStatus() != timeNotSet && lastDisplayMode == DISP_TIME) {

    displayStatusUpdate();

    if (minute() != previousMinute) { // Update the display only if time has changed
      previousMinute = minute();
      updateDisplay(DISP_TIME);
    }

  }

  static uint8_t previousSecond = 0;
  if (timeStatus() != timeNotSet) {
    if (second() != previousSecond && serialClockEnabled) { // Update the display only if time has changed
      previousSecond = second();
      serialClockDisplay();
    }
  }


  // Display timeout
  if (millis() >= displayTimeoutMillis && displayTimeoutMillis != 0) {
    Serial.println("Display timeout");
    updateDisplay(DISP_TIME);
    displayTimeoutMillis = 0;
  }

}


/************************************** updateDisplay ***********************/

void updateDisplay(uint8_t displayMode) {

  //  Serial.print(" ***** display update - ");
  //  Serial.print(displayMode);
  //  Serial.println(" update ****");

  lastDisplayMode = displayMode;

  //display.clearIndicators();
  display.clearSomeIndicators();      // Set alarm indicators too ?

    if (displayMode == DISP_BLANK) {
      display.setChar(0, ' ');
      display.setChar(1, ' ');
      display.setChar(2, ' ');
      display.setChar(3, ' ');
      display.clearIndicators();
      return;
    }

  if (displayMode <= DISP_SLEEP) {
    // time, alarms, sleep, vol, show both commas (move separate from this if block?)
    display.setIndicator(IND_BOT_COL, true);
    display.setIndicator(IND_TOP_COL, true);

  }



  if (displayMode == DISP_TIME) {
    Serial.print("  ---------> Time is: ");
    serialClockDisplay();
    digitalClockDisplay();  // Handles display "empty" on batt power
    updateAlarmIndicators();
  }

  else {
    if (displayMode == DISP_AL1) {
      Serial.print("  ---------> Alarm 1: ");
      Serial.print(alarm1Hours);
      Serial.print(":");
      Serial.println(alarm1Minutes);
      Serial.println();
      displayAlarm1();
    }


    else if (displayMode == DISP_AL2) {
      Serial.print("  ---------> Alarm 2: ");
      Serial.print(alarm2Hours);
      Serial.print(":");
      Serial.println(alarm2Minutes);
      Serial.println();
      displayAlarm2();
    }

    else if (displayMode == DISP_AL1_TXT || displayMode == DISP_AL2_TXT) {

      display.setChar(1, 'A');
      display.setChar(2, 'L');
      display.setChar(0, ' ');

      if (displayMode == DISP_AL1_TXT) {
        display.setDigit(3, 1);
      }
      else {
        display.setDigit(3, 2);
      }

    }

    else if (displayMode == DISP_VOL) {
      Serial.print("  ---------> Volume: ");
      Serial.print(volume);
      Serial.println();
      displayVolume();
    }

    else if (displayMode == DISP_FREQ) {
      Serial.print("  ---------> Freq: ");
      //      Serial.print(float(freq / 100.0));
      Serial.println();

      displayFrequency();
    }

    else if (displayMode == DISP_SLEEP) {
      displaySleep();
    }

    else if (displayMode == DISP_OFF_TXT) {
      display.setChar(0, ' ');
      display.setDigit(1, 0); // Change to char while we're at it ... TODO
      display.setChar(2, 'F');
      display.setChar(3, 'F');
      display.setIndicator(IND_SLEEP, false); // kinda workaround since it updates all the time uselessly

      updateAlarmIndicators();
    }

  }


  display.setIndicator(IND_FM, audioEnabled);

}

void updateAlarmIndicators() {
  //Serial.println("Alarm indicators update");

  if (alarm1Status == AL_ENABLED || alarm1Status == AL_WAS_TRIG) {
    display.setIndicator(IND_AL1, true);
  }
  else if (alarm1Status == AL_DISABLED) {
    display.setIndicator(IND_AL1, false);
  }

  if (alarm2Status == AL_ENABLED || alarm2Status == AL_WAS_TRIG) {
    display.setIndicator(IND_AL2, true);
  }
  else if (alarm2Status == AL_DISABLED) {
    display.setIndicator(IND_AL2, false);
  }

}


void displayStatusUpdate() {

  // We don't care much about NTP when on battery, nest them

  static bool dot_state = false;

  static bool lastNTPState = NTPState;

  static uint32_t previousMillis = 0;



  uint32_t currentMillis = millis();

  if ((uint32_t)(currentMillis - previousMillis) >= DOT_FLASH_DELAY) {
    //Serial.println("blink");

    if (powerSource == PWR_BATT) {
      dot_state = !dot_state;
      display.setIndicator(IND_BOT_COL, dot_state);
      display.setIndicator(IND_TOP_COL, dot_state);
    }
    else {

      if (NTPState == false) {
        dot_state = !dot_state;
        display.setIndicator(IND_BOT_COL, dot_state);
        display.setIndicator(IND_TOP_COL, !dot_state);
      }

      if (lastNTPState != NTPState && NTPState == true) {
        dot_state = !dot_state;
        display.setIndicator(IND_BOT_COL, dot_state);
        display.setIndicator(IND_TOP_COL, !dot_state);
        lastNTPState = NTPState;
      }



    }


    // ************** here ******************
    static bool al_dot_state = false;

    if (alarm1Status == AL_SNOOZED  || alarm1Status == AL_TRIGGERED) {
      al_dot_state = !al_dot_state;
      display.setIndicator(IND_AL1, al_dot_state);
    }

    if (alarm2Status == AL_SNOOZED || alarm2Status == AL_TRIGGERED) {
      al_dot_state = !al_dot_state;
      display.setIndicator(IND_AL2, al_dot_state);
    }

    previousMillis = currentMillis;
  } // timed


  lastNTPState = NTPState;

}


void digitalClockDisplay() {

#ifdef BATT_OVERRIDE2
  if (powerSource == PWR_BATT) {
    display.setChar(0, ' ');
    display.setChar(1, ' ');
    display.setChar(2, ' ');
    display.setChar(3, ' ');
    return;
  }

#endif

  time_t local = myTZ.toLocal(now());


  uint8_t tens = hour(local);
  uint8_t ones = tens % 10;

  //  Serial.print("z/t b: ");
  //  Serial.println(tens);

  if (tens > 12) {
    tens = tens - 12;
    display.setIndicator(IND_PM, true);
  }
  else {
    display.setIndicator(IND_PM, false);
  }

  //  Serial.print("z a: ");
  //  Serial.println(tens);
  //  Serial.println();


  if (tens >= 10) {
    display.setDigit(0, 1);
  }
  else {
    display.setChar(0, ' ');
  }

  tens = tens % 10;

  if (tens >= 10) {
    tens = tens - 10;
  }

  display.setDigit(1, tens);



  /******************************/

  tens = minute(local);
  ones = tens % 10;
  tens = tens / 10;
  tens = tens % 10;

  // Print the minutes digit by digit
  display.setDigit(2, tens);


  display.setDigit(3, ones);

  if (serialClockEnabled) {
    serialClockDisplay();
  }

}

void displayDashes() { // Fixed
  display.setChar(0, ' ');
  for (uint8_t x = 1; x < DIGIT_COUNT; x++) {
    display.setChar(x, '-');
  }
}



void displaySleep() {

  bool temp_hours = (sleepMinutes / 60);
  int8_t temp_minutes = (sleepMinutes % 60);  // extract the minutes (ditch the hours)

  display.setChar(0, ' ');

  display.setDigit(1, temp_hours);

  display.setDigit(2, (temp_minutes / 10));

  display.setDigit(3, (sleepMinutes % 10));

  display.setIndicator(IND_SLEEP, true); // kinda workaround since it updates all the time uselessly
}


void displayFrequency() {
  
  Serial.print("displayFrequency -- ");
  uint16_t freq = getFrequency() / 10 ;

  display.setIndicator(IND_DOT, true);

  // ex. 10610 / 10 = 1061

  if (freq < 1000) {
    display.setChar(0, ' ');
  }
  else {
    display.setDigit(0, 1);
    freq = freq % 1000;
  }


  display.setDigit(1, (freq / 100));
  freq = freq % 100;
  display.setDigit(2, (freq / 10));
  freq = freq % 10;
  display.setDigit(3, freq);

}


void displayVolume() {

  display.setChar(0, ' ');

  display.setChar(1, 'U');

  if (volume < 10) {
    display.setChar(2, ' ');
  }
  else {
    display.setDigit(2, (volume / 10));
  }

  display.setDigit(3, (volume % 10));
}

void displayAlarm1() {

  uint8_t tens = alarm1Hours;
  uint8_t ones = tens % 10;

  //  Serial.print("z/t b: ");
  //  Serial.println(tens);

  if (tens > 12) {
    tens = tens - 12;
    display.setIndicator(IND_PM, true);
  }
  else {
    display.setIndicator(IND_PM, false);
  }

  //  Serial.print("z a: ");
  //  Serial.println(tens);
  //  Serial.println();


  if (tens >= 10) {
    display.setDigit(0, 1);
  }
  else {
    display.setChar(0, ' ');
  }

  tens = tens % 10;

  if (tens >= 10) {
    tens = tens - 10;
  }

  display.setDigit(1, tens);


  tens = alarm1Minutes;
  ones = tens % 10;
  tens = tens / 10;
  tens = tens % 10;

  // Print the minutes digit by digit
  display.setDigit(2, tens);
  display.setDigit(3, ones);

  if (alarm1Status == AL_ENABLED) {
    display.setIndicator(IND_AL1, true);
  }
  else if (alarm1Status == AL_DISABLED) {
    display.setIndicator(IND_AL1, false);
  }


}

void displayAlarm2() {

  uint8_t tens = alarm2Hours;
  uint8_t ones = tens % 10;

  //  Serial.print("z/t b: ");
  //  Serial.println(tens);

  if (tens > 12) {
    tens = tens - 12;
    display.setIndicator(IND_PM, true);
  }
  else {
    display.setIndicator(IND_PM, false);
  }

  //  Serial.print("z a: ");
  //  Serial.println(tens);
  //  Serial.println();


  if (tens >= 10) {
    display.setDigit(0, 1);
  }
  else {
    display.setChar(0, ' ');
  }

  tens = tens % 10;

  if (tens >= 10) {
    tens = tens - 10;
  }

  display.setDigit(1, tens);


  tens = alarm2Minutes;
  ones = tens % 10;
  tens = tens / 10;
  tens = tens % 10;

  // Print the minutes digit by digit
  display.setDigit(2, tens);
  display.setDigit(3, ones);

  if (alarm2Status == AL_ENABLED) {
    display.setIndicator(IND_AL2, true);
  }
  else if (alarm2Status == AL_DISABLED) {
    display.setIndicator(IND_AL2, false);
  }

}



void displaySetMinIntensity() {

  Serial.print("Saved Intensity: ");
  Serial.println(displayIntensity);

  savedDisplayIntensity = displayIntensity;

  displayIntensity = MIN_INTENSITY;

  Serial.print("New Intensity: ");
  Serial.println(displayIntensity);

  display.setIntensity(displayIntensity);
}

void displayRestoreIntensity() {
  displayIntensity = savedDisplayIntensity;
  Serial.print("Intensity: ");
  Serial.println(displayIntensity);
  display.setIntensity(displayIntensity);
}

void displaySetIntensity(uint8_t intensity) {

  if (intensity > 15) {
    intensity = 15;
  }

  displayIntensity = intensity;
  savedDisplayIntensity = displayIntensity;

  display.setIntensity(displayIntensity);    // Set display intensity

  Serial.print("Intensity xx: ");
  Serial.println(displayIntensity);
}

void dimDisplay() {

  // Ignore the dim calls if we're on battery power.
  if (powerSource == PWR_BATT) {
    return;
  }

  if (displayIntensity == 0) {
    displayIntensity = MAX_INTENSITY;
  }
  else {
    displayIntensity--;
  }


  Serial.print("intensity: ");
  Serial.println(displayIntensity);

  displaySetIntensity(displayIntensity);
}


void saveIntensity(uint8_t intensity) {
  EEPROM.write(EE_ADDR_INTENSITY, intensity);
  EEPROM.commit();
}


uint8_t restoreIntensityEE() {

  uint8_t readValue = EEPROM.read(EE_ADDR_INTENSITY);;

  if (readValue != 0xFF) { // if configured
    Serial.println("Intensity configured");
  }
  else {
    readValue = DEFAULT_INTENSITY;
    saveIntensity(readValue);
    Serial.println("Intensity not configured - setting default");
  }

  return readValue;
}


void printIntensityEE() {

  Serial.println("Reading intensity EEPROM values");

  uint8_t readValue = EEPROM.read(EE_ADDR_INTENSITY);

  if (readValue != 0xFF) {
    Serial.print("     Configured  ");
  }

  Serial.print("     Saved value: ");
  Serial.println(EEPROM.read(EE_ADDR_INTENSITY));

}
