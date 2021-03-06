#include "MCP_Display.h"
#include "MCP23017.h"

MCP23017 disp_exp_low, disp_exp_high;


MCP_DISPLAY::MCP_DISPLAY() {}


void MCP_DISPLAY::setDigit(uint8_t digit, uint8_t index) {

  if (digit != 0) {
    digitShadow[digit] = (digitShadow[digit] & ~0x7F) | (num_map[index] & 0x7F);
  }
  else {
    digitShadow[digit] = (digitShadow[digit] & ~0x06) | (num_map[index] & 0x06);
  }

  updateOne(digit);

}


void MCP_DISPLAY::setChar(uint8_t digit, uint8_t character) {

  uint8_t temp_data;

  switch (character) {



    case '0':
      temp_data = num_map[0]; 
      break;


    case ' ':
      temp_data = 0b00000000;
      break;
    case '-':
      temp_data = 0b01000000;
      break;
    case '_':
      temp_data = 0b00001000;
      break;

    case ')':
    case ']':
      temp_data = 0b00001111;
      break;

    case 'A':
    case 'a':
      temp_data = num_map[10]; // Same as 0xA
      break;

    case 'B':
    case 'b':
      temp_data = num_map[11]; // Same as 0xB
      break;

    case 'C':
      temp_data = 0b00111001;
      break;
    case 'c':
      temp_data = num_map[12]; // Same as 0xc
      break;

    case 'D':
    case 'd':
      temp_data = num_map[13]; // Same as 0xD
      break;

    case 'E':
    case 'e':
      temp_data = num_map[14]; // Same as 0xE
      break;

    case 'F':
    case 'f':
      temp_data = num_map[15]; // Same as 0xF
      break;

    case 'G':
    case 'g':
      temp_data = num_map[9]; // Same as 9
      break;

    case 'H':
    case 'x':
    case 'X':
      temp_data = 0b01110110;
      break;
    case 'h':
      temp_data = 0b01110100;
      break;

    case 'I':
      temp_data = num_map[1];
      break;
    case 'i':
      temp_data = 0b00000100;
      break;

    case 'J':
      temp_data = 0b00001110;
      break;
    case 'j':
      temp_data = 0b00001100;
      break;

    case 'l':
      temp_data = 0b00110000;
      break;
    case 'L':
      temp_data = 0b00111000;
      break;

    case 'N':
    case 'n':
      temp_data = 0b01010100;
      break;

    case 'O':
      temp_data = num_map[0]; // Same as 0
      break;
    case 'o':
      temp_data = 0b01011100;
      break;

    case 'P':
    case 'p':
      temp_data = 0b01110011;
      break;

    case 'Q':
    case 'q':
      temp_data = 0b01100111;
      break;

    case 'R':
    case 'r':
      temp_data = 0b01010000;
      break;

    case 'S':
    case 's':
      temp_data = num_map[5];
      break;

    case 'U':
    case 'V':
      temp_data = 0b00111110; // Same as 0
      break;
    case 'u':
    case 'v':
      temp_data = 0b00011100;
      break;

    case 'Y':
    case 'y':
      temp_data = 0b01101110;
      break;

    case 'Z':
    case 'z':
      temp_data = num_map[2];
      break;

    default:
      temp_data = 0x00;
  }


  if (digit != 0) {
    digitShadow[digit] = (digitShadow[digit] & ~0x7F) | (temp_data & 0x7F);
  }
  else {
    digitShadow[digit] = (digitShadow[digit] & ~0x06) | (temp_data & 0x06);
  }


  updateOne(digit);

}



void MCP_DISPLAY::setup() {

  disp_exp_high.begin(DISP_ADDR_HIGH, SCL_PIN, SDA_PIN);
  disp_exp_low.begin(DISP_ADDR_LOW, SCL_PIN, SDA_PIN);

/*
  disp_exp_high.pinMode(PORT_A, OUTPUT);
  disp_exp_high.pinMode(PORT_B, OUTPUT);
  disp_exp_low.pinMode(PORT_A, OUTPUT);
  disp_exp_low.pinMode(PORT_B, OUTPUT);
*/

  for (uint8_t x = 0; x <= 7; x++) {
    //Serial.println(x);
    disp_exp_low.pinMode(PORT_A, x, OUTPUT);
    disp_exp_low.pinMode(PORT_B, x, OUTPUT);

    disp_exp_high.pinMode(PORT_A, x, OUTPUT);
    disp_exp_high.pinMode(PORT_B, x, OUTPUT);
  }

  ledcSetup(DISP_INT_CHAN, DISP_PWM_FREQ, DISP_PWM_BITS);
  ledcAttachPin(INTENSITY_PIN, DISP_INT_CHAN);

  clearDisplay();        // Clear the display

}


void MCP_DISPLAY::updateOne(uint8_t digit) {

  switch (digit) {

    case 0:
      disp_exp_low.writeByte(PORT_B, ~digitShadow[digit]); // Invert because CA
      break;
    case 1:
      disp_exp_low.writeByte(PORT_A, ~digitShadow[digit]); // Invert because CA
      break;
    case 2:
      disp_exp_high.writeByte(PORT_B, ~digitShadow[digit]); // Invert because CA
      break;
    case 3:
      disp_exp_high.writeByte(PORT_A, ~digitShadow[digit]); // Invert because CA
      break;
  }
}


void MCP_DISPLAY::updateAll() {
  disp_exp_low.writeByte(PORT_B, ~digitShadow[0]); // Invert because CA
  disp_exp_low.writeByte(PORT_A, ~digitShadow[1]); // Invert because CA
  disp_exp_high.writeByte(PORT_B, ~digitShadow[2]); // Invert because CA
  disp_exp_high.writeByte(PORT_A, ~digitShadow[3]); // Invert because CA
}


void MCP_DISPLAY::clearDisplay() {
  digitShadow[0] = 0x00;
  digitShadow[1] = 0x00;
  digitShadow[2] = 0x00;
  digitShadow[3] = 0x00;
  updateAll();
}


void MCP_DISPLAY::shutdown(bool state) {

  Serial.print("shutdown: ");
  Serial.println(state);

  if (state == false) {
    // turn it on, restore intensity
    setIntensity(currentIntensity);
  }
  else {
    // Directly write 0, so we don't have to touch the intensity value
    ledcWrite(DISP_INT_CHAN, 0);
  }
}





void MCP_DISPLAY::setIntensity(uint8_t array_index) {
  //Serial.print("Index: ");
  Serial.println(array_index);

  if (array_index > MAX_INTENSITY) {
    array_index = MAX_INTENSITY;
  }
/*
  Serial.print("Index checked: ");
  Serial.print(array_index);
  Serial.print("    LUT Value: ");
  Serial.println(intensity_lut[array_index]);
*/
  currentIntensity = array_index;

  ledcWrite(DISP_INT_CHAN, intensity_lut[array_index]);

}


void MCP_DISPLAY::setIndicator(uint8_t ind_id, bool state) {


  if (ind_id == IND_FM) {
    bitWrite(digitShadow[3], 7, state);
    updateOne(3);
  }
  else if (ind_id == IND_AL2) {
    bitWrite(digitShadow[2], 7, state);
    updateOne(2);
  }
  else if (ind_id == IND_DOT) {
    bitWrite(digitShadow[1], 7, state);
    updateOne(1);
  }
  else { // all the rest on digit 0

    switch (ind_id) {
      case IND_TOP_COL:
        bitWrite(digitShadow[0], 4, state);
        break;
      case IND_BOT_COL:
        bitWrite(digitShadow[0], 5, state);
        break;
      case IND_AL1:
        bitWrite(digitShadow[0], 7, state);
        break;
      case IND_SLEEP:
        bitWrite(digitShadow[0], 0, state);
        break;
      case IND_PM:
        bitWrite(digitShadow[0], 3, state);
        break;
    }

    updateOne(0);
  }

} // indicators set/clear



void MCP_DISPLAY::clearIndicators() {

// Dirty as hell but just for testing. TODO
    for (uint8_t x = 0; x < 8; x++) {
        setIndicator(x, false);
    }


    updateAll();
}

void MCP_DISPLAY::clearSomeIndicators() {

// Dirty as hell but just for testing. TODO

    setIndicator(IND_DOT, false);
    setIndicator(IND_BOT_COL, false);
    setIndicator(IND_TOP_COL, false);
    setIndicator(IND_PM, false);
    


    updateAll();
}



void MCP_DISPLAY::setAllOn() {
  digitShadow[0] = 0xFF;
  digitShadow[1] = 0xFF;
  digitShadow[2] = 0xFF;
  digitShadow[3] = 0xFF;
  updateAll();
}


void MCP_DISPLAY::test_indicators() {
  Serial.println("Cycle ind");

  clearDisplay();

  setIndicator(IND_FM, true);
  delay(125);
  setIndicator(IND_FM, false);
  setIndicator(IND_AL2, true);
  delay(125);
  setIndicator(IND_AL2, false);
  setIndicator(IND_DOT, true);
  delay(125);
  setIndicator(IND_DOT, false);
  setIndicator(IND_BOT_COL, true);
  delay(125);
  setIndicator(IND_BOT_COL, false);
  setIndicator(IND_TOP_COL, true);
  delay(125);
  setIndicator(IND_TOP_COL, false);
  setIndicator(IND_PM, true);
  delay(125);
  setIndicator(IND_PM, false);
  setIndicator(IND_SLEEP, true);
  delay(125);
  setIndicator(IND_SLEEP, false);
  setIndicator(IND_AL1, true);
  delay(250);
  setIndicator(IND_AL1, false);
  setIndicator(IND_SLEEP, true);
  delay(125);
  setIndicator(IND_SLEEP, false);
  setIndicator(IND_PM, true);
  delay(125);
  setIndicator(IND_PM, false);
  setIndicator(IND_TOP_COL, true);
  delay(125);
  setIndicator(IND_TOP_COL, false);
  setIndicator(IND_BOT_COL, true);
  delay(125);
  setIndicator(IND_BOT_COL, false);
  setIndicator(IND_DOT, true);
  delay(125);
  setIndicator(IND_DOT, false);
  setIndicator(IND_AL2, true);
  delay(125);
  setIndicator(IND_AL2, false);
  setIndicator(IND_FM, true);
  delay(125);
  setIndicator(IND_FM, false);
  delay(125);
  clearDisplay();
  delay(1000);

}


void MCP_DISPLAY::test_seq() {

  for (uint8_t x = 0; x < 16; x++) {
    //    Serial.println(x);
    setDigit(3, x);
    delay(150);
  }


  //clearDisplay();
  setChar(3, '_');
  delay(1000);

  for (uint8_t x = 0; x < 16; x++) {
    //    Serial.println(x);

    setDigit(2, x);
    delay(150);
  }


  //clearDisplay();
  setChar(2, '_');
  delay(1000);


  for (uint8_t x = 0; x < 16; x++) {
    //    Serial.println(x);
    setDigit(1, x);
    delay(150);
  }

  //clearDisplay();
  setChar(1, '_');
  delay(1000);

  setDigit(0, 1);
  delay(1000);

  clearDisplay();
  delay(1000);


  //  Serial.println();
}

void MCP_DISPLAY::testDispSeg() {

  for (uint8_t x = 0; x < 8; x++) {
    //Serial.println(x);
    disp_exp_high.digitalWrite(PORT_A, x, 0);
    disp_exp_high.digitalWrite(PORT_B, x, 0);
    disp_exp_low.digitalWrite(PORT_A, x, 0);
    delay(250);
  }

  delay(1000);

  for (uint8_t x = 0; x < 8; x++) {
    //Serial.println(x);
    disp_exp_high.digitalWrite(PORT_A, x, 1);
    disp_exp_high.digitalWrite(PORT_B, x, 1);
    disp_exp_low.digitalWrite(PORT_A, x, 1);
    delay(250);
  }


  for (uint8_t x = 0; x < 8; x++) {
    //Serial.println(x);
    disp_exp_low.digitalWrite(PORT_B, x, 0);
    delay(250);
  }

  delay(1000);

  for (uint8_t x = 0; x < 8; x++) {
    //Serial.println(x);
    disp_exp_low.digitalWrite(PORT_B, x, 1);
    delay(250);
  }

}
