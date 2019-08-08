#ifndef BEENHERE
#include "MorseTutor.h"
#endif


extern "C" {
#include "Utilities.h"
};

/*****
  Purpose: The STM32 does not actually have any EEPROM, so we have to fake it with flash memory. This code defines where the
           page in flash memory resides that will be used as EEPROM

  Parameter list:
    void

  Retrun value:
    void
*****/
void DefineEEPROMPage()
{
  // **** EEPROM.PageBase0 = 0x801f000;     // EEPROM base address. Everything indexed from this address
  // **** EEPROM.PageSize  = 0x400;         // 1024 bytes of EEPROM
}


/*****
  Purpose: Set default configuration data to EEPROM

  Parameter list:
    void

  Retrun value:
    void
*****/
void SaveEEPROMDefaults()
{
  int status;
  uint16_t temp;

  temp = 18;
  // ***** todo status = EEPROM.write((uint16_t) WORDSPERMINUTE,   temp);
  if (!status) {
    Serial.print("EEPROM wpm write sucks, Status = ");
    Serial.println(status);
  }
  temp = 700;
  // ***** todo status = EEPROM.write((uint16_t) SIDETONE,         temp);
  if (!status) {
    Serial.print("EEPROM SIDETONE write sucks, Status = ");
    Serial.println(status);
  }

  // ***** todo temp = PA8;
  temp = 8;

  // ***** todo status = EEPROM.write((uint16_t) WHICHISDITPADDLE, temp);
  if (!status) {
    Serial.print("EEPROM WHICHISDITPADDLE write sucks, Status = ");
    Serial.println(status);
  }
  temp = 10;
  // ***** todo status = EEPROM.write((uint16_t) FARSWORTHSPEED,   temp);
  if (!status) {
    Serial.print("EEPROM FARSWORTHSPEED write sucks, Status = ");
    Serial.println(status);
  }
  temp = 25;
  // ***** todo status = EEPROM.write((uint16_t) KOCHSPEED,        temp);
  if (!status) {
    Serial.print("EEPROM KOCHSPEED write sucks, Status = ");
    Serial.println(status);
  }
  temp = 1;
  // ***** todo status = EEPROM.write((uint16_t) ENCODINGACTIVE,   temp);
  if (!status) {
    Serial.print("EEPROM ENCODINGACTIVE write sucks, Status = ");
    Serial.println(status);
  }
}

/*****
  Purpose: Save configuration data to EEPROM
  Parameter list:
    void

  Retrun value:
    void
*****/
void SaveConfigData()
{
  int status;


  // **store in NVS
  setParameterState(WORDSPERMINUTE);
  setParameterState(SIDETONE);
  setParameterState(ENCODINGACTIVE);
  setParameterState(KOCHSPEED);
  setParameterState(VOLUME);

// this is all EEPROM

  // ****** todo status = EEPROM.write((uint16_t) WORDSPERMINUTE,   wordsPerMinute);
  if (status) {
    Serial.print("EEPROM wpm write sucks, Status = ");
    Serial.println(status);
  }
  // ****** todo status = EEPROM.write((uint16_t) SIDETONE,         sidetoneFrequency);
  if (status) {
    Serial.print("EEPROM sidetoneFrequency write sucks, Status = ");
    Serial.println(status);
  }
  // ****** todo status = EEPROM.write((uint16_t) WHICHISDITPADDLE, ditPaddle);
  if (status) {
    Serial.print("EEPROM ditPaddle write sucks, Status = ");
    Serial.println(status);
  }
  // ****** todo status = EEPROM.write((uint16_t) FARSWORTHSPEED,   farnsworthWPM);
  if (status) {
    Serial.print("EEPROM farnsworthWPM write sucks, Status = ");
    Serial.println(status);
  }
  // ****** todo status = EEPROM.write((uint16_t) KOCHSPEED,       kochSpeed);
  if (status) {
    Serial.print("EEPROM kochSpeed write sucks, Status = ");
    Serial.println(status);
  }
  // ***** todo
  // status = EEPROM.write((uint16_t) ENCODINGACTIVE,  encodingType);


  if (status) {
    Serial.print("EEPROM encodingType write sucks, Status = ");
    Serial.println(status);
  }
}

/*****
  Purpose: Read configuration data from EEPROM

  Parameter list:
    void

  Retrun value:
    void
*****/
void ReadConfigData()
{
  int status;

  // ***** todo figure this out
  status = 0;


  /*
    // ***** todo status = EEPROM.read((uint16) WORDSPERMINUTE,   &wordsPerMinute);
    if (status) Serial.println("EEPROM wpm write sucks");
    // ***** todo status = EEPROM.read((uint16) SIDETONE,         &sidetoneFrequency);
    if (status) Serial.println("EEPROM sidetone write sucks");
    // ***** todo status = EEPROM.read((uint16) WHICHISDITPADDLE, &ditPaddle);
    if (status) Serial.println("EEPROM ditPaddle write sucks");
    // ***** todo status = EEPROM.read((uint16) FARSWORTHSPEED,   &farnsworthWPM);
    if (status) Serial.println("EEPROM farnsworthWPM write sucks");
    // ***** todo status = EEPROM.read((uint16) KOCHSPEED,        &kochSpeed);
    if (status) Serial.println("EEPROM kochSpeed write sucks");
    // ***** todo status = EEPROM.read((uint16) ENCODINGACTIVE,   &encodingType);
    if (status) Serial.println("EEPROM encodingType write sucks");
  */
}

/*****
  Purpose: Debugging read of EEPROM and print to Serial monitor

  Parameter list:
    void

  Retrun value:
    void
*****/
void ShowConfigData()
{
  Serial.print("wordsPerMinute = ");
  Serial.println(wordsPerMinute);

  Serial.print("sidetoneFrequency = ");
  Serial.println(sidetoneFrequency);

  //Serial.print("ditPaddle = ");
  //Serial.println(ditPaddle);

  Serial.print("farnsworthWPM = ");
  Serial.println(farnsworthWPM);

  Serial.print("kochSpeed = ");
  Serial.println(kochSpeed);

  Serial.print("encodingType = ");
  Serial.println(encodingType);

}

/*****
  Purpose: Debugging read of EEPROM and print to Serial monitor

  Parameter list:
    void

  Retrun value:
    uint16        0 if okay, non-zero otherwise
*****/
//uint16 WriteEEPROMValue(uint16 address, uint16 value)
int WriteEEPROMValue(int address, int value)
{
  // ***** todo return EEPROM.write(address, value);
  return 0;
}
