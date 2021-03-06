/*

  Todo:
     -  Long press / help Clock/Mem key saves current station (if playing) in EEPROM or whatever
     -  If we're battery powered (and the display "off" code is done), show the time for displayTimeout value.


  Working:
    - Power key:
        - Audio on/off
        - Alarms off

    - V- Key:
        - Alarm 1 toggle
        - Volume down (w/ repeat)

    - V+ Key:
        - Alarm 1 toggle
        - Volume up (w/ repeat)

    - F- Key:
        - Alarm 1 hours (w/ repeat, AL1 key down)
        - Alarm 2 hours (w/ repeat, AL2 key down)
        - Time hours (w/ repeat, clock key down)

    - F+ Key:
        - Alarm 1 minutes (w/ repeat, AL1 key down)
        - Alarm 2 minutes (w/ repeat, AL2 key down)
        - Time minutes (w/ repeat, clock key down)



*/

#include "MCP23008.h"
MCP23008 expander;

uint8_t interruptEventCounter = 0;


struct Keys {
  uint8_t pinState = 0;
  uint8_t keyState = 0;
  uint32_t downTime = 0;
  bool needTimeout = 0; // used for key repeat
  //} key[LAST_KEY + 1];
} key[8];

void writeLed(bool state) {
  expander.digitalWrite(LED_PIN, state);
}

void setupKeys() {

  pinMode(MCP_INT_PIN, INPUT_PULLUP);   // Configure MCU input pin for MCP interrupt

  expander.begin(MCP_ADDR, SCL_PIN, SDA_PIN);         // Start Expander

  // Set all key pins as input
  for (uint8_t x = 0; x <= 7; x++) {
    expander.pinMode(x, INPUT);
    expander.invertInput(x, true);
    expander.enableInterrupt(x, IF_CHANGED);
  }

  expander.pinMode(LED_PIN, OUTPUT);

} // setupKeys




void checkKeys() {

  // check for interrupt
  if (!digitalRead(MCP_INT_PIN)) {

#ifdef INT_DEBUG
    interruptEventCounter++;

    Serial.println();
    Serial.print("INTERRUPT EVENT!  (Count: ");
    Serial.print(interruptEventCounter);
#endif

    uint8_t intPin = expander.getInterruptPin();

    key[intPin].pinState = expander.getInterruptPinValue(intPin);
    key[intPin].downTime = millis();

    //    Serial.print(") --- > Pin ");
    //    Serial.print(intPin);
    //    Serial.print("   Value: ");
    //    Serial.print(key[intPin].pinState);
    //    Serial.println();

    Serial.print("Pin ");
    Serial.print(intPin);
    Serial.print("   Value: ");
    Serial.print(key[intPin].pinState);
    Serial.print("  --> ");

    handleKey(intPin, false);
    Serial.println();
  } // if interrupt



  // check for key timeouts, etc...

  for (uint8_t x = 0; x <= 7; x++) {

    if (key[x].needTimeout == true) {


      unsigned long currentMillis = millis();
      if ((unsigned long)(currentMillis - key[x].downTime) >= KEY_TIMEOUT) {
        Serial.print("KEY TIMEOUT: ");
        Serial.println(x);
        handleKey(x, true);        // handle key
        key[x].downTime = currentMillis;        // reload timer
      }

    }
  }

} // checkKeys



void handleKey(uint8_t keyID, bool repeat) {


  if (keyID == KEY_CLK) {

    static uint8_t repeatCount = 0;

    if (key[keyID].pinState == KEY_STATE_DOWN) {

      if (audioEnabled) {

        if (repeat) {
          repeatCount++;
          Serial.print("CLK DOWN - repeated: ");
          Serial.println(repeatCount);

          if (repeatCount == 5) {
            Serial.println("5 -saving"); // save, blink, etc
            saveRadioStation();

            updateDisplay(DISP_BLANK);
            delay(500);
            updateDisplay(DISP_FREQ);
            delay(500);
            updateDisplay(DISP_BLANK);
            delay(500);
            updateDisplay(DISP_FREQ);
            delay(500);
            displayTimeout();
          }
        }
        else {
          Serial.println("CLK DOWN - not repeated");
          //display frequency
          updateDisplay(DISP_FREQ);
          //displayTimeout();
        }

        Serial.print("CLK DOWN - repeated: ");
        Serial.println(repeatCount);
      }

      key[keyID].needTimeout = true;

    }
    else if (key[keyID].pinState == KEY_STATE_UP) {
      Serial.println("CLK UP");

      repeatCount = 0;
      displayTimeout();
      key[keyID].needTimeout = false;
    }
  } // clock key



  // ***** Power key ****
  if (keyID == KEY_PWR) {
    if (key[keyID].pinState == KEY_STATE_DOWN) {
      Serial.println("PWR DOWN");


      if (alarm1Status >= AL_TRIGGERED || alarm2Status >= AL_TRIGGERED) { // >= makes it work for snoozed as well


        if (alarm1Status >= AL_TRIGGERED) {
          alarm1Status = AL_WAS_TRIG;
          Serial.print("Alarm 1: ");
          Serial.println(alarm1Status);
        }
        if (alarm2Status >= AL_TRIGGERED) {
          alarm2Status = AL_WAS_TRIG;
          Serial.print("Alarm 2: ");
          Serial.println(alarm2Status);
        }
        disableAudio();
      }
      else {
        if (!audioEnabled) {
          enableAudio();
          updateDisplay(DISP_FREQ);
          displayTimeout();
        }
        else {
          disableAudio();
          sleepMinutes = -1;
          Serial.println("Sleep off");
        }
        //        toggleAudio();
      }
    }
    else if (key[keyID].pinState == KEY_STATE_UP) {
      Serial.println("PWR UP");
    }
  } // Power key

  /*************** VOLUME DOWN KEY **************************/
  if (keyID == KEY_V_DN) {
    if (key[keyID].pinState == KEY_STATE_DOWN) {
      Serial.println("V- Down");

      if (!audioEnabled) {
        if (alarm1Status == AL_DISABLED) {
          Serial.println("AL1 enable");
          alarm1Status = AL_ENABLED;
        }
        else {
          Serial.println("AL1 disable");
          alarm1Status = AL_DISABLED;
        }
        updateDisplay(DISP_AL1);
        saveAlarm1State();
      }
      else {
        volumeDown();
        updateDisplay(DISP_VOL);
        key[keyID].needTimeout = true;
      }
    }
    else if (key[keyID].pinState == KEY_STATE_UP) {
      Serial.println("V- Up");
      displayTimeout();
      key[keyID].needTimeout = false;

      if (alarm1NeedsUpdate == true) {
        alarm1NeedsUpdate = false;
        Serial.println("Potato");
        saveAlarm1Time();
      }
    }
  } // Vol down Key


  /*************** VOLUME UP KEY **************************/
  if (keyID == KEY_V_UP) {
    if (key[keyID].pinState == KEY_STATE_DOWN) {
      Serial.println("V+ Down");

      if (!audioEnabled) {
        if (alarm2Status == AL_DISABLED) {
          Serial.println("AL2 enable");
          alarm2Status = AL_ENABLED;
        }
        else {
          Serial.println("AL2 disable");
          alarm2Status = AL_DISABLED;
        }
        saveAlarm2State();
        updateDisplay(DISP_AL2);
      }
      else {
        volumeUp();
        updateDisplay(DISP_VOL);
        key[keyID].needTimeout = true;
      }
    }
    else if (key[keyID].pinState == KEY_STATE_UP) {
      Serial.println("V+ Up");
      displayTimeout();
      key[keyID].needTimeout = false;

      if (alarm2NeedsUpdate == true) {
        alarm2NeedsUpdate = false;
        saveAlarm2Time();
      }
    }
  } // Vol up Key



  if (keyID == KEY_F_DN) {
    if (key[keyID].pinState == KEY_STATE_DOWN) {
      Serial.println("F- Down");

      // If we have the Alarm 1 key down, adjust Alarm 1 hours
      if (key[KEY_V_DN].pinState == KEY_STATE_DOWN) {

        if (alarm1Hours < 23) {
          alarm1Hours++;
        }
        else {
          alarm1Hours = 0;
        }

        Serial.print("Alarm 1 hours: ");
        Serial.println(alarm1Hours);
        alarm1NeedsUpdate = true;
        updateDisplay(DISP_AL1);
        key[keyID].needTimeout = true;

      } // AL1

      // If we have the Alarm 2 key down, adjust Alarm 2 hours
      else if (key[KEY_V_UP].pinState == KEY_STATE_DOWN) {

        if (alarm2Hours < 23) {
          alarm2Hours++;
        }
        else {
          alarm2Hours = 0;
        }

        Serial.print("Alarm 2 hours: ");
        Serial.println(alarm2Hours);
        alarm2NeedsUpdate = true;
        updateDisplay(DISP_AL2);
        key[keyID].needTimeout = true;
      } // AL2

      // If we have the clock key down, adjust TIME hours
      else if (key[KEY_CLK].pinState == KEY_STATE_DOWN) {

        if (timeHours < 23) {
          timeHours++;
        }
        else {
          timeHours = 0;
        }

        Serial.print("Time hours: ");
        Serial.println(timeHours);
        updateDisplay(DISP_TIME);
        key[keyID].needTimeout = true;
      } // Time

      else if (key[KEY_DIM].pinState == KEY_STATE_DOWN) {

        bool temp_hours = (sleepMinutes / 60); // Since we only go from 0 to 1:59, we only have 2 states for the hour
        if (temp_hours == 0) {
          sleepMinutes = sleepMinutes + 60;
        }
        else {
          sleepMinutes = sleepMinutes - 60;
        }
        updateDisplay(DISP_SLEEP);
        key[keyID].needTimeout = true;
      }

      else {
        if (audioEnabled && !repeat) {
          tuneDown();
          updateDisplay(DISP_FREQ);
          key[keyID].needTimeout = true;
        }
        else if (audioEnabled && repeat) {
          // TODO: wait for seek done before display or w/e?
          seekDown();
        }

      }
    }
    else if (key[keyID].pinState == KEY_STATE_UP) {
      Serial.println("F- Up");
      if (audioEnabled && key[KEY_DIM].pinState != KEY_STATE_DOWN) {
        displayTimeout();
      }
      key[keyID].needTimeout = false;
    }
  } // freq down Key


  if (keyID == KEY_F_UP) {
    if (key[keyID].pinState == KEY_STATE_DOWN) {
      Serial.println("F+ Down");

      // If we have the Alarm 1 key down, adjust Alarm 1 minutes
      if (key[KEY_V_DN].pinState == KEY_STATE_DOWN) {
        if (alarm1Minutes < 59) {
          alarm1Minutes++;
        }
        else {
          alarm1Minutes = 0;
        }
        Serial.print("Alarm 1 minutes: ");
        Serial.println(alarm1Minutes);
        alarm1NeedsUpdate = true;
        updateDisplay(DISP_AL1);
        key[keyID].needTimeout = true;

      }

      // If we have the Alarm 2 key down, adjust Alarm 2 minutes
      else if (key[KEY_V_UP].pinState == KEY_STATE_DOWN) {
        if (alarm2Minutes < 59) {
          alarm2Minutes++;
        }
        else {
          alarm2Minutes = 0;
        }
        Serial.print("Alarm 2 minutes: ");
        Serial.println(alarm2Minutes);
        alarm2NeedsUpdate = true;
        updateDisplay(DISP_AL2);
        key[keyID].needTimeout = true;
      }

      // If we have the clock key down, adjust Time minutes
      else if (key[KEY_CLK].pinState == KEY_STATE_DOWN) {
        if (timeMinutes < 59) {
          timeMinutes++;
        }
        else {
          timeMinutes = 0;
        }
        Serial.print("Time minutes: ");
        Serial.println(timeMinutes);
        updateDisplay(DISP_TIME);
        key[keyID].needTimeout = true;
      }

      else if (key[KEY_DIM].pinState == KEY_STATE_DOWN) {
        int8_t temp_minutes = (sleepMinutes % 60);  // extract the minutes (ditch the hours)

        temp_minutes++;

        if (temp_minutes == 60) {
          temp_minutes = 0;
        }

        bool temp_hours = (sleepMinutes / 60); // Since we only go from 0 to 1:59, we only have 2 states for the hour

        sleepMinutes = (temp_hours * 60) + temp_minutes;

        // if sleepMinutes is set to zero here, disable it
        if (sleepMinutes == 0) {
          sleepMinutes = -1;
        }

        updateDisplay(DISP_SLEEP);
        key[keyID].needTimeout = true;
      }
      else {
        if (audioEnabled && !repeat) {
          tuneUp();
          updateDisplay(DISP_FREQ);
          key[keyID].needTimeout = true;
        }
        else if (audioEnabled && repeat) {
          seekUp();
        }
      }
    }
    else if (key[keyID].pinState == KEY_STATE_UP) {
      Serial.println("F+ Up");
      if (audioEnabled && key[KEY_DIM].pinState != KEY_STATE_DOWN) {
        displayTimeout();
      }
      key[keyID].needTimeout = false;
    }
  } // freq up Key



  if (keyID == KEY_DIM) {
    if (key[keyID].pinState == KEY_STATE_DOWN) {
      Serial.println("DIM DOWN");

      if (alarm1Status == AL_TRIGGERED || alarm2Status == AL_TRIGGERED) {

        if (alarm1Status == AL_TRIGGERED) {
          Serial.print("Snooze AL1 - ");
          alarm1Status = AL_SNOOZED;
          alarm1SnoozeMin = minute() + SNOOZE_DELAY;
          alarm1SnoozeSec = second();

          if (alarm1SnoozeMin >= 60) {
            alarm1SnoozeMin = alarm1SnoozeMin - 60;
          }

          Serial.print("Snooze min: ");
          Serial.println(alarm1SnoozeMin);
          Serial.print("Snooze sec: ");
          Serial.println(alarm1SnoozeSec);
        }

        if (alarm2Status == AL_TRIGGERED) {
          Serial.print("Snooze AL2 - ");
          alarm2Status = AL_SNOOZED;
          alarm2SnoozeMin = minute() + SNOOZE_DELAY;
          alarm2SnoozeSec = second();

          if (alarm2SnoozeMin >= 60) {
            alarm2SnoozeMin = alarm2SnoozeMin - 60;
          }

          Serial.print("Snooze min: ");
          Serial.println(alarm2SnoozeMin);
          Serial.print("Snooze sec: ");
          Serial.println(alarm2SnoozeSec);
        }

        disableAudio();
      }

      else if (audioEnabled && sleepMinutes == -1) {
        sleepMinutes = SLEEP_DEFAULT_MIN;
        updateDisplay(DISP_SLEEP);
        Serial.println("Sleep enabled");
      }
      else if (sleepMinutes != -1) {
        updateDisplay(DISP_SLEEP);
        Serial.println("show sleep time");
      }
      else {
        dimDisplay();
        key[keyID].needTimeout = true;
      }
    }
    else if (key[keyID].pinState == KEY_STATE_UP) {
      Serial.println("DIM UP");
      key[keyID].needTimeout = false;

      if (sleepMinutes != -1) {
        updateDisplay(DISP_SLEEP);
        displayTimeout();
      }
    }


  } // Dim key

}
