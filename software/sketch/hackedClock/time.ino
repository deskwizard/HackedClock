

extern bool NTPState;

void setupTime() {

  // Set time library update function and update interval
  setSyncProvider(updateTime);
  setSyncInterval(RTC_UPDATE_INTERVAL);

  Serial.print("DST?: ");
  Serial.println(myTZ.locIsDST(now()));

}


time_t updateTime() {

  Serial.print("Trying RTC... ");

  time_t rtcTime = RTC.get();

  if (forceBadRTC) {
    Serial.println("RTC invalidated.");
    return 0;
  }


  if (rtcTime <= DEFAULT_TIME) {    // TODO: Add < bad time (2106 something like that) too.
    Serial.println("RTC time is invalid.");
    return 0;
  }
  else {
    Serial.println("RTC time is Valid, time updated.");
    return rtcTime + 1;
  }

}


void handleSleep() {

  static uint8_t previousMinute = 0;

  if (minute() != previousMinute) { // Update the display only if time has changed
    previousMinute = minute();

    //    Serial.println("sleep handle minutes");

    if (sleepMinutes != -1) {

      sleepMinutes--;
      if (sleepMinutes == 0) {
        Serial.println("Sleep over");
        sleepMinutes = -1;
        // Only turn audio off if we don't have an alarm triggered
        if (alarm1Status != AL_TRIGGERED && alarm2Status != AL_TRIGGERED) {
          disableAudio();
        }
      }

      Serial.print("Sleep minutes left: ");
      Serial.println(sleepMinutes);
    }
  }

}



// ************** Alarms Start **************** 


void setupAlarms() {

  // check if time is set
  if (timeStatus() != timeNotSet) {

    Serial.println("Time is valid, fetching alarms");

    // HERE ******************************************************
    restoreAlarms(); // From EEPROM - NEW

    Serial.println();
  }
  else {
    Serial.println("Time not valid");
  }

  updateAlarmIndicators();

  Serial.println();

}





void handleAlarms() {

  uint32_t currentMillis = millis();
  static uint32_t previousMillis = currentMillis;

  if ((uint32_t)(currentMillis - previousMillis) >= 1000) {
    //    Serial.println("Alarm Check");

    time_t local = myTZ.toLocal(now());

    if (hour(local) == alarm1Hours && minute(local) == alarm1Minutes && alarm1Status == AL_ENABLED) {

      Serial.println(" ---- DEBUG: AL1 trigger");

      //if (alarm1Status == AL_ENABLED) {
      Serial.print("Alarm 1 triggered at ");
      serialClockDisplay();
      alarm1Status = AL_TRIGGERED;
      enableAudio(); // start audio
      updateDisplay(DISP_AL1_TXT);
      displayTimeout();
      //}
    }
    else if (minute(local) != alarm1Minutes && alarm1Status == AL_WAS_TRIG) {
      // restore alarm state to enabled here ??
      Serial.print("Alarm 1 was triggered reset at ");
      serialClockDisplay();
      alarm1Status = AL_ENABLED;
    }


    if (hour(local) == alarm2Hours && minute(local) == alarm2Minutes && alarm2Status == AL_ENABLED) {

      Serial.println(" ---- DEBUG: AL2 trigger");

      //if (alarm2Status == AL_ENABLED) {
      Serial.print("Alarm 2 triggered at ");
      serialClockDisplay();
      alarm2Status = AL_TRIGGERED;
      enableAudio(); // start audio
      updateDisplay(DISP_AL2_TXT);
      displayTimeout();
      //}
    }
    else if (minute(local) != alarm2Minutes && alarm2Status == AL_WAS_TRIG) {
      // restore alarm state to enabled here ??
      Serial.print("Alarm 2 was triggered reset at ");
      serialClockDisplay();
      alarm2Status = AL_ENABLED;
    }


    previousMillis = currentMillis;
  }


  // Snoozing
  if (alarm1Status == AL_SNOOZED && (alarm1SnoozeMin == minute() && alarm1SnoozeSec == second()) ) {

    // Re-trigger alarm
    Serial.print("Alarm 1 re-triggered at ");
    serialClockDisplay();
    alarm1Status = AL_TRIGGERED;
    enableAudio(); // start audio
    updateDisplay(DISP_AL1_TXT);
    displayTimeout();
  }

  if (alarm2Status == AL_SNOOZED && (alarm2SnoozeMin == minute() && alarm2SnoozeSec == second()) ) {

    // Re-trigger alarm
    Serial.print("Alarm 2 re-triggered at ");
    serialClockDisplay();
    alarm2Status = AL_TRIGGERED;
    enableAudio(); // start audio
    updateDisplay(DISP_AL2_TXT);
    displayTimeout();
  }

}




// ********** EEPROM Save/Restore ***********

void saveAlarm1State() {

  Serial.println("saving alarm 1 state");
  Serial.print("state: ");
  Serial.println(alarm1Status);

  EEPROM.write(EE_ADDR_AL1_ENABLED, alarm1Status);
  EEPROM.commit();
}


void saveAlarm1Time() {     // When you save the time also save the state (always going to be AL_ENABLE anyway)?

  alarm1Status = AL_ENABLED;

  Serial.println("saving alarm 1 ");
  Serial.print("state: ");
  Serial.println(alarm1Status);
  Serial.print("Time: ");
  Serial.print(alarm1Hours);
  Serial.print(":");
  Serial.println(alarm1Minutes);

  EEPROM.write(EE_ADDR_AL1_ENABLED, alarm1Status);
  EEPROM.write(EE_ADDR_AL1_HR, alarm1Hours);
  EEPROM.write(EE_ADDR_AL1_MIN, alarm1Minutes);
  EEPROM.commit();
}


void saveAlarm2State() {

  Serial.println("saving alarm 2 state");
  Serial.print("state: ");
  Serial.println(alarm2Status);

  EEPROM.write(EE_ADDR_AL2_ENABLED, alarm2Status);
  EEPROM.commit();
}


void saveAlarm2Time() {     // When you save the time also save the state (always going to be AL_ENABLE anyway)?

  alarm2Status = AL_ENABLED;

  Serial.println("saving alarm 2 ");
  Serial.print("state: ");
  Serial.println(alarm2Status);
  Serial.print("Time: ");
  Serial.print(alarm2Hours);
  Serial.print(":");
  Serial.println(alarm2Minutes);

  EEPROM.write(EE_ADDR_AL2_ENABLED, alarm2Status);
  EEPROM.write(EE_ADDR_AL2_HR, alarm2Hours);
  EEPROM.write(EE_ADDR_AL2_MIN, alarm2Minutes);
  EEPROM.commit();
}

void restoreAlarms() {

  Serial.println();

  uint8_t readValue = EEPROM.read(EE_ADDR_AL1_ENABLED);
  uint8_t hr = 0;
  uint8_t min = 0;

  // AL1
  if (readValue != 0xFF) {

    hr = EEPROM.read(EE_ADDR_AL1_HR);
    min = EEPROM.read(EE_ADDR_AL1_MIN);

    Serial.print("Alarm 1 Configured: ");
    Serial.println(readValue);
    Serial.print("      Time: ");
    Serial.print(hr);
    Serial.print(":");
    Serial.println(min);

    // Set alarm state
    alarm1Status = readValue;
    alarm1Hours = hr;
    alarm1Minutes = min;

  }
  else {
    Serial.println("Alarm 1 Not configured");
    alarm1Status = AL_DISABLED;
  }

  Serial.println(alarm1Status);


  readValue = EEPROM.read(EE_ADDR_AL2_ENABLED);
  hr = 0;
  min = 0;

  // AL2
  if (readValue != 0xFF) {

    hr = EEPROM.read(EE_ADDR_AL2_HR);
    min = EEPROM.read(EE_ADDR_AL2_MIN);

    Serial.print("Alarm 2 Configured: ");
    Serial.println(readValue);
    Serial.print("      Time: ");
    Serial.print(hr);
    Serial.print(":");
    Serial.println(min);

    // Set alarm state
    alarm2Status = readValue;
    alarm2Hours = hr;
    alarm2Minutes = min;

  }
  else {
    Serial.println("Alarm 2 Not configured");
    alarm2Status = AL_DISABLED;
  }

  Serial.println();

}



void serialClockDisplay() {

  time_t local = myTZ.toLocal(now());

  // digital clock display of the time
  Serial.print(hour(local));
  printDigits(minute(local));
  printDigits(second(local));
  Serial.print(" ");
  Serial.print(day(local));
  Serial.print(".");
  Serial.print(month(local));
  Serial.print(".");
  Serial.print(year(local));
  Serial.println();
}

void printDigits(int digits) {

  // utility for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


// Function to print time
void printTime(time_t t) {
  sPrintI00(hour(t));
  sPrintDigits(minute(t));
  sPrintDigits(second(t));
  Serial.print(' ');
  Serial.print(dayShortStr(weekday(t)));
  Serial.print(' ');
  Serial.print(monthShortStr(month(t)));
  Serial.print(' ');
  sPrintI00(day(t));
  Serial.print(' ');
  Serial.println(year(t));
}

//Print an integer in "00" format (with leading zero).
//Input value assumed to be between 0 and 99.
void sPrintI00(int val) {
  if (val < 10) Serial.print('0');
  Serial.print(val, DEC);
  return;
}

//Print an integer in ":00" format (with leading zero).
//Input value assumed to be between 0 and 99.
void sPrintDigits(int val) {
  Serial.print(':');
  if (val < 10) Serial.print('0');
  Serial.print(val, DEC);
}
