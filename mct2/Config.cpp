#ifndef BEENHERE
#include "MorseTutor.h"
#endif

extern "C" {
#include "Utilities.h"
};

/*****

  Purpose: Sets default values for the system

  Parameter list:
    void

  Return value:
    void
*****/
void SetDefaults()
{
  if (wordsPerMinute == 0) {                  // In case it's the first time here
    wordsPerMinute = 15;
  }
  SetDitLength(wordsPerMinute);
  //sidetoneFrequency = FREQUENCY;              // Def 700Hz
  encodingType      = FARNSWORTHENCODING;
  targetWPM         = GOALSPEED;              // Def 35WPM
  farnsworthDelay = 1200 / FARNSWORTHSTART;   // Def 5WPM
  displayState      = 1;
}

/*****
  Purpose: To change the code speed of the keyer

  Parameter list:
    void

  Return value:
    void
*****/
void SetKeyerSpeed()
{
  char temp[4];
  int8_t result;
  int i;
  static int val = 1;

  if (wordsPerMinute == 0) {
    wordsPerMinute = 15;
  }

  // *******myMenu.eraseMenus(tft);
  myMenu.eraseMenus();
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setCursor(70, 72);
  M5.Lcd.print("Current WPM");

  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(120, 110);
  M5.Lcd.print(wordsPerMinute);

  while (!M5.BtnA.read()) // is button A pressed, asserted low)
  {
    result = ReadEncoder();                                   //Hacky stuff again...
    if (result == 0)
    {
      continue;
    } else
    {
      if (result == 1)
      {
        //val++;                      // Clockwise          (CW)
        val = 2;
      }
      else
      {
        //val--;                      // Counter-clockwise  (CCW)
        val = -2;
      }

      if (val == 2 || val == -2)
      { // It takes 2 pulses to make a rotation
        if (val > 0)
        { // CW??
          //         if (result == 1)
          dir = 1;
        } else
        { // Nope, CCW
          dir = -1;
        }
        wordsPerMinute  += dir;                        // Works because encorderDirection can be +/-
        SetDitLength(wordsPerMinute);

        if (wordsPerMinute > WPMMAX)
        { // Check max wpm
          wordsPerMinute = WPMMAX;
        }
        if (wordsPerMinute < WPMMIN)
        { // Check min wpm
          wordsPerMinute = WPMMIN;
        }
        myMenu.eraseMenus();
        M5.Lcd.setTextColor(GREEN, BLACK);
        //M5.Lcd.setCursor(70, 72);
        M5.Lcd.setCursor(100, 72);
        M5.Lcd.print("Current WPM");

        M5.Lcd.setTextColor(WHITE, BLACK);
        //M5.Lcd.setCursor(120, 110);
        M5.Lcd.setCursor(150, 110);
        M5.Lcd.print(wordsPerMinute);
        dir = 0;
        val = 1;
      }
    }
  }

  // ButtonA is no longer pressed
  // **** todo
  // **** i = EEPROM.update((uint16) WORDSPERMINUTE, wordsPerMinute);

  //#define EEPROM_SAME_VALUE 0 //whatever
  //#define FLASH_COMPLETE 0 //whatever

  //  i = 0;



  //  if (i != EEPROM_SAME_VALUE || i != FLASH_COMPLETE) {              // Something went wrong...
  //    Serial.print("EEPROM wpm write sucks, Status = ");
  //    Serial.println(i);
  //  }

  // the global wordsPerMinute has the latest value
  // store it in NVS

  // this is new for the ESP32
  // **store in NVS
  setParameterState(WORDSPERMINUTE);

  SetDitLength(wordsPerMinute);                                     // Activate new speed
  tutorMode == SENDSTATE;
  //SendCode((char) 0b11010);       // 'C'
  //SendCode((char) 0b11101);       // 'Q'
  SendCode((char) 0b10001);       // 'V'
  SendCode((char) 0b10001);       // 'V'
  tutorMode == RECEIVESTATE;
}

/*****
  Purpose: To change the sidetone

  Parameter list:
    void

  Return value:
    void
*****/

void SetNewSidetone()
{
  char temp[4];
  int8_t result;
  int frequencyTemp;
  static int val = 1;

  frequencyTemp = sidetoneFrequency;

  myMenu.eraseMenus();
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setCursor(60, 100);
  M5.Lcd.print("Sidetone Frequency");

  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(120, 130);
  M5.Lcd.print(sidetoneFrequency);///////

  while (!M5.BtnA.read()) // is button A pressed, asserted low)
  {
    result = ReadEncoder();
    if (result == 0)
    {
      continue;
    } else
    {
      if (result == 1)
      {
        //val++;                      // Clockwise          (CW)
        val = 2;
      }
      else
      {
        //val--;                      // Counter-clockwise  (CCW)
        val = -2;
      }

      if (val == 2 || val == -2) {  // It takes 2 pulses to make a rotation
        if (val > 0) {              // CW??
          //         if (result == 1) {
          dir = 1;
        } else {                    // Nope, CCW
          dir = -1;
        }
        frequencyTemp += dir * FREQUENCYINCREMENT;      // Bump the frequncy
        if (frequencyTemp > MAXFREQ) {                  // Check max frequncy
          frequencyTemp = MAXFREQ;
        }
        if (frequencyTemp < MINFREQ) {                  // Check min frequncy
          frequencyTemp = MINFREQ;
        }

        //    tft.setTextColor(WHITE, BLACK);
        // itoa(wordsPerMinute, temp, DEC);

        //M5.Lcd.setCursor(120, 130);
        //M5.Lcd.println(frequencyTemp);                      // Show frequncy

        myMenu.eraseMenus();
        M5.Lcd.setTextColor(GREEN, BLACK);
        M5.Lcd.setCursor(60, 100);
        M5.Lcd.print("Sidetone Frequency");

        M5.Lcd.setTextColor(WHITE, BLACK);
        M5.Lcd.setCursor(120, 130);
        M5.Lcd.print(frequencyTemp);///////

        dir = 0;
        val = 1;
      }
    }
  }
  // always update the global before storing in NVS
  // setParameterState() upddates the NVS from the global
  sidetoneFrequency = frequencyTemp;
  // this is new for the ESP32
  // **store in NVS
  setParameterState(SIDETONE);
  //playTone(2000);

  //noTone(SPEAKERPIN);                                // Shut up!
}

/*****
  Purpose: To set whether using standard or Farnsworth encoding
  Parameter list:
    void

  Return value:
    void
*****/


// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

//#define NORMALENCODING         0      // Standard encoding
//#define FARNSWORTHENCODING     1      // Requires target and Farnsworth speeds

int SetEncodingType()
{
  int firstRow = TOPDEADSPACE + 20;
  int direction = 0;
  static int passCalls = 0;
  static int flag = 1;
  int val, result;

  myMenu.eraseMenus();
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setCursor(60, firstRow);
  M5.Lcd.print("Encoding Type");

  M5.Lcd.setTextColor(BLACK, WHITE);
  M5.Lcd.setCursor(10, firstRow + 30);
  M5.Lcd.print(" Farnsworth");
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setCursor(150, firstRow + 30);
  M5.Lcd.print(" Standard");

  // a global
  encodingType = 1;// Display defaults to Farnsworth (type = 1)
  // If buttons B or C not pressed, use this


  while (!M5.BtnA.read())
  {
    // result normally 0
    result = ProcessEncoder();

    if (result) // a change requested
    {
      if (result == 1)
      {
        // move CW, Normal Encoding
        //val++;                        // Clockwise          (CW)
        val = 2;
        if (encodingType == 1) // a change requested
        {
          M5.Lcd.setTextColor(GREEN, BLACK);
          M5.Lcd.setCursor(10, firstRow + 30);
          M5.Lcd.print(" Farnsworth");
          M5.Lcd.setTextColor(BLACK, WHITE);
          M5.Lcd.setCursor(150, firstRow + 30);
          M5.Lcd.print(" Standard");
          encodingType = 0;
        }
      }
      else
      {
        if (encodingType == 0) // a change requested
        {
          //val--;                        // Counter-clockwise  (CCW)
          val = -2;
          M5.Lcd.setTextColor(BLACK, WHITE);
          M5.Lcd.setCursor(10, firstRow + 30);
          M5.Lcd.print(" Farnsworth");
          M5.Lcd.setTextColor(GREEN, BLACK);
          M5.Lcd.setCursor(150, firstRow + 30);
          M5.Lcd.print(" Standard");
          encodingType = 1;
        }
      }

    }
  }
  // wait for button A to be pressed
  while (M5.BtnA.read())
    ;
}
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

/*****
  Purpose: This sets the ultimate WPM speed the user hopes to reach

  Parameter list:
    void

  Return value:
    int       the desired speed
*****/
int SetTargetWPM()
{
  int firstRow = TOPDEADSPACE + 85;
  int wpm;
  int direction = 0;
  static int passCalls = 0;
  static int flag = 1;
  int8_t result;
  int localDir;
  static int val = 1; // here we go again

  if (wordsPerMinute == 0)
  {
    wpm = 25;
  } else
  {
    wpm = wordsPerMinute;
  }

  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setCursor(90, firstRow);
  M5.Lcd.print("Target WPM");

  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(150, firstRow + 30);
  M5.Lcd.print(wpm);


  //while (digitalRead(ENCODERSWITCH1) != LOW)
  while (!M5.BtnA.read()) // is button A pressed, asserted low)
  {
    result = ProcessEncoder();

    if (result)
    {
      if (result == 1)
      {
        //val++;                      // Clockwise          (CW)
        val = 2;
      }
      else
      {
        //val--;                      // Counter-clockwise  (CCW)
        val = -2;
      }
      wpm += val; // a complication
      if (wpm > WPMMAX)
      { // Check max wpm
        wpm = WPMMAX;
      }
      if (wpm < WPMMIN)
      { // Check min wpm
        wpm = WPMMIN;
      }
      M5.Lcd.setCursor(130, firstRow + 30);
      M5.Lcd.println("                         ");
      M5.Lcd.setCursor(150, firstRow + 30);
      M5.Lcd.println(wpm);             // Show target speed
      MyDelay(200UL);
      val = 0;
    }
  }

  kochSpeed = wpm;

  setParameterState(KOCHSPEED);
  return wpm;     // New target speed
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++
uint16_t setVol()
{
  int vol;
  int8_t result;
  int localDir;
  static int val = 1; // here we go again

  vol = int(volume * 10.0);

  int firstRow = TOPDEADSPACE + 20;
  int direction = 0;
  static int passCalls = 0;
  static int flag = 1;
  int tempi = 0;

  myMenu.eraseMenus();
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setCursor(130, 100);
  M5.Lcd.print("Volume");

  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(150, firstRow + 80);
  M5.Lcd.print(vol);///////

  while (!M5.BtnA.read()) // is button A pressed, asserted low)
  {
    result = ProcessEncoder();

    if (result)
    {
      if (result == 1)
      {
        tempi++;
        //val++;                      // Clockwise          (CW)
        val = 2;
      }
      else
      {
        //val--;                      // Counter-clockwise  (CCW)
        tempi--;
        val = -2;
      }
      vol += tempi; // a complication
      if (vol > 10.0)
      { // Check max wpm
        vol = 10.0;
      }
      if (vol < 1)
      { // Check min wpm
        vol = 1.0;
      }

      myMenu.eraseMenus();
      M5.Lcd.setTextColor(GREEN, BLACK);
      M5.Lcd.setCursor(130, 100);
      M5.Lcd.print("Volume");

      M5.Lcd.setTextColor(WHITE, BLACK);
      M5.Lcd.setCursor(150, firstRow + 80);
      M5.Lcd.print(vol);///////
      MyDelay(200UL);
      val = 1;
      tempi = 0;
    }
  }

  volume = float(vol) * 0.1;
  // **store in NVS
  setParameterState(VOLUME);

  tutorMode = SENDSTATE;
  //SendCode((char) 0b11010);       // 'C'
  //SendCode((char) 0b11101);       // 'Q'
  SendCode((char) 0b10001);       // 'V'
  SendCode((char) 0b10001);       // 'V'

  tutorMode = RECEIVESTATE;

  return vol;     // New volume
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++


/*****
  Purpose: The Farnsworth method for learning sends letters at the speed you hope to ultimately reach (e.g., targetWPM),
          but instead of a letter space at the target speed, the Farnsworth method has the character spacing at a much
          lower speed. For example, you might hope to get to 35wpm, but set the Farnsworth (spacing) speed at 5wpm. The
          advantage is that you listen for rhythms rather than dits and dahs.

  Parameter list:
    void

  Return value:
    int       the desired speed
*****/
int SetFarnsworthWPM()
{
  int firstRow = TOPDEADSPACE + 155;
  int wpm;
  int8_t result;
  static int val = 1; // here we go again

  wpm = WPMMIN;      // Start really slow
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setCursor(68, firstRow);
  M5.Lcd.print("Farnsworth WPM");

  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(150, firstRow + 30);
  M5.Lcd.print(wpm);
  while (!M5.BtnA.read()) // is button A pressed, asserted low)
  {
    result = ProcessEncoder();

    if (result)
    {
      if (result == 1)
      {
        //val++;                        // Clockwise          (CW)
        val = 2;
      }
      else
      {
        //val--;                        // Counter-clockwise  (CCW)
        val = -2;
      }
      wpm += val;
      if (wpm > targetWPM)
      { // Check max wpm
        wpm = targetWPM;
      }
      if (wpm < WPMMIN)
      { // Check min wpm
        wpm = WPMMIN;
      }

      M5.Lcd.setCursor(130, firstRow + 30);
      M5.Lcd.println("                         ");
      M5.Lcd.setCursor(150, firstRow + 30);
      M5.Lcd.println(wpm);               // Show target speed
      MyDelay(200UL);
      val = 0;
    }
  }
  return wpm;                         // New farnsworth speed
}


/*****
  Purpose: This function lets the user change the paddle that sends a string of dits

  Parameter list:
    void

  Return value:
    int       the desired choice
*****/
//int SetDitPaddle() not used
