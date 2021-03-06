

extern int8_t displayIntensity;

void setupPower() {

  pinMode(PWR_DETECT_PIN, INPUT);
  delay(100);

  powerSource = !digitalRead(PWR_DETECT_PIN); // Invert it so that handlePower() triggers now

  handlePower();
}


void handlePower() {
  static bool lastPowerSource = powerSource;
  static uint8_t savedIntensity = displayIntensity;

  powerSource = digitalRead(PWR_DETECT_PIN);

  if (powerSource != lastPowerSource) {
    Serial.print("Power source changed to: ");
    //    Serial.println(powerSource);

    if (powerSource == PWR_BATT) {
      Serial.println("Battery Power");
      savedIntensity = displayIntensity;

      Serial.print("Intensity qq: ");
      Serial.println(savedIntensity);

      if (displayIntensity > BATT_PWR_INTENSITY) {
        displaySetIntensity(BATT_PWR_INTENSITY);
      }

    }
    else {
      Serial.println("AC Power");
      displaySetIntensity(savedIntensity);
    }

    updateDisplay(DISP_TIME);
    lastPowerSource = powerSource;
  }
}
