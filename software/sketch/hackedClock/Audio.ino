#include <RDA5807.h>  //    https://github.com/pu2clr/RDA5807 (available in library manager)

RDA5807 radio;

#define AMP_EN_PIN  23

#define DEFAULT_STATION 10690
#define DEFAULT_VOL  3
#define MAX_VOL     15

uint8_t volume = 0;
uint16_t currentStation = 0;


void setupAudio() {
  pinMode(AMP_EN_PIN, OUTPUT);
  digitalWrite(AMP_EN_PIN, HIGH); // Make sure amp is off (not really necessary)
  radio.softReset();
  restoreVolume();
  restoreRadioStation();
}


void enableAudio() {

  audioEnabled = true;

  radio.powerUp();

  radio.setMono(true);

  radio.setSeekThreshold(10); // Sets RSSI Seek Threshold (0 to 127)

  radio.setFrequency(currentStation); // Set initial frequency (*100)

  //  radio.setBass(true);
  radio.setVolume(volume);

  Serial.println("Audio enabled");
  Serial.print("V: ");
  Serial.println(radio.getVolume());

  // Enable amplifier
  digitalWrite(AMP_EN_PIN, HIGH);

}


void disableAudio() {
  audioEnabled = false;
  radio.powerDown();
  Serial.println("Audio disabled");
  updateDisplay(DISP_OFF_TXT);
  displayTimeout();

  // Disable amplifier
  digitalWrite(AMP_EN_PIN, LOW);
}


void volumeUp() {
  if (volume != MAX_VOL) {
    volume++;
  }
  Serial.print("Vol: ");
  Serial.println(volume);
  radio.setVolume(volume);
}


void volumeDown() {
  if (volume != 1) {    // Let's assume 0 is mute for now
    volume--;
  }
  Serial.print("Vol: ");
  Serial.println(volume);
  radio.setVolume(volume);
}


void seekDown() {
  radio.seek(RDA_SEEK_WRAP, RDA_SEEK_DOWN, showFrequency);  // showFrequency will be called by the seek function during the process.
  delay(200);
  //showFrequency(); // <<< display timeout set
  Serial.println("Seek down finished");
  currentStation = radio.getRealFrequency();
  printRadio();
}


void seekUp() {
  radio.seek(RDA_SEEK_WRAP, RDA_SEEK_UP, showFrequency);  // showFrequency will be called by the seek function during the process.
  delay(200);
  //showFrequency(); // <<< display timeout set
  Serial.println("Seek up finished");
  currentStation = radio.getRealFrequency();
  printRadio();
}


void showFrequency() {
  Serial.print("----> Seeking - Freq.: ");
  Serial.println(float(radio.getRealFrequency()) / 100.0);
  updateDisplay(DISP_FREQ);
}


void tuneUp() {
  Serial.println("tune Up");

  radio.setFrequencyUp();
  currentStation = radio.getRealFrequency();
  printRadio();
}

void tuneDown() {
  Serial.println("tuneDown");

  radio.setFrequencyDown();
  currentStation = radio.getRealFrequency();
  printRadio();
}


uint16_t getFrequency() {
  return radio.getRealFrequency();
}



void saveVolume(uint8_t volume) {
  EEPROM.write(EE_ADDR_VOL, volume);
  EEPROM.commit();
}


void restoreVolume() {

  uint8_t readValue = EEPROM.read(EE_ADDR_VOL);;

  if (readValue == 0xFF) { // if not configured
    readValue = DEFAULT_VOL;
    saveVolume(readValue);
    Serial.print("Volume not configured - setting default: ");

  }
  else {
    Serial.print("Volume configured: ");
  }
  Serial.println(readValue);

  volume = readValue;

}


void saveRadioStation() {

  // If we save station, set configured byte
  Serial.print("Saving station: ");
  Serial.println(currentStation);

  EEPROM.write(EE_ADDR_RADIO_LOW, uint8_t(currentStation & 0x00FF)); // clear the high bits before cast
  EEPROM.write(EE_ADDR_RADIO_HIGH, uint8_t(currentStation >> 8));

  EEPROM.commit();

}



void restoreRadioStation() {

  Serial.print("Restoring radio station... ");

  uint16_t station = ( (EEPROM.read(EE_ADDR_RADIO_HIGH) << 8) | EEPROM.read(EE_ADDR_RADIO_LOW));

  if (station == 0xFFFF) { // if not configured
    // Not configured
    Serial.print("Radio NOT configured - using default: ");
    station = DEFAULT_STATION;
    saveRadioStation();
  }
  else {
    // Configured
    Serial.print("Radio configured: ");
  }

  Serial.println(station);
  Serial.println();

  currentStation = station;

}


void printRadio() {

  // RSSI value printed here just after a tune is bogus, then again, debug only.
  // Seek is just pointless to print really.
  delay(250);   // Delay for RSSI, 250 okay-ish for tune


  Serial.print("Frequency: ");
  Serial.print(float(radio.getRealFrequency()) / 100.0);
  Serial.print("    RSSI: ");
  Serial.println(radio.getRssi());
}
