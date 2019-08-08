#ifndef BEENHERE
#include "MorseTutor.h"
#endif


/*****
  Purpose: to send a Morse code dit

  Paramter list:
  void

  Return value:
  void

  CAUTION: Assumes that a global named ditlen holds the value for dit spacing
*****/
#ifndef BEENHERE
#include "MorseTutor.h"
#endif


/****
  Purpose: to send a Morse code dit

  Paramter list:
  void

  Return value:
  void

  CAUTION: Assumes that a global named ditlen holds the value for dit spacing
*****/


const float Pi = 3.14159;
const int delay_MSEC = 36; //number of delay_interval(s) in 1 msec

void playTone(unsigned long msecLength)
{
  float sidetoneFrequencyLocal;

  sidetoneFrequencyLocal = sidetoneFrequency + 480.0; // TODO *** needs calibration

  // 2*Pi*f*t at 8000 sps
  //float theta_increment = 2.0 * Pi * (sidetoneFrequency * 0.000125); //8ksps
  float theta_increment = 2.0 * Pi * (sidetoneFrequencyLocal * 0.000020833);//48ksps


  float theta  = 0.0;
  float outVal;

  //uint16_t delay_interval = ((uint16_t) 83); // 8Ksps
  uint16_t delay_interval = ((uint16_t) 21); // 48Ksps


  //digitalWrite(TEST_PIN, HIGH);


  for (int i = 0; i < (msecLength * 36) - 600 ; i++)
  {

    outVal = sinf(theta) * volume;

    outVal = (unsigned char) (outVal * 127.0 + 128.0);


    dacWrite(SPEAKER_PIN, outVal);
    dacWrite(EXT_SPEAKER, outVal);

    delayMicroseconds(delay_interval);

    theta += theta_increment;
    if (theta > 2.0 * Pi)
    {
      theta -= 2.0 * Pi;
    }

  }

  //digitalWrite(TEST_PIN, LOW);

  //dacWrite(SPEAKER_PIN, 0);
  //dacWrite(EXT_SPEAKER, 0);

  //delay(1); // in msec

  //M5.Speaker.tone(700, 3000);

}

void dit()
{

  //tone(SPEAKERPIN, sidetoneFrequency);  // Send sidetone sound signal...
  //M5.Speaker.setVolume(5);
  //M5.Speaker.update();
  //M5.Speaker.tone(sidetoneFrequency);//Squarewave

  playTone(ditlen);
  MyDelay(ditlen);
  
  //noTone(SPEAKERPIN); // off
  //M5.Speaker.mute();
}

/*****
  Purpose: to send a Morse code dah

  Paramter list:
  void

  Return value:
  void

  CAUTION: Assumes that a global named ditlen holds the value for dit spacing
*****/
void dah()
{
  // tone is a square wave with no amplitude adjust
  //tone(SPEAKERPIN, sidetoneFrequency); // Send sidetone sound signal...
  //Serial.print(sidetoneFrequency);
  //M5.Speaker.tone(sidetoneFrequency);
  
  playTone(3UL * ditlen);

  //MyDelay(3UL * ditlen);
  //noTone(SPEAKERPIN);
  //M5.Speaker.mute();
  MyDelay(ditlen);
}

/*****
  Purpose: to provide spacing between letters

  Paramter list:
  void

  Return value:
  void

  CAUTION: Assumes that a global named ditlen holds the value for dit spacing
*****/
void LetterSpace()
{
  if (encodingType == FARNSWORTHENCODING)
    MyDelay(3UL * 240UL);
  else
    MyDelay(3UL * ditlen);
}
/*****
  Purpose: to provide spacing between words

  Paramter list:
  void

  Return value:
  void

  CAUTION: Assumes that a global named ditlen holds the value for dit spacing
*****/
void WordSpace()
{
  MyDelay(7 * ditlen);
}

/*****
  Purpose: to send a Morse code character

  Paramter list:
  char code       the code for the letter to send

  Return value:
  void
*****/
void SendCode(char code)
{
  int i;


  for (i = 7; i >= 0; i--)
    if (code & (1 << i))
      break;
  for (i--; i >= 0; i--) {
    if (code & (1 << i))
    {
      dah();
    }
    else
      dit();
  }
  LetterSpace();
}


/*****
  Purpose: to send a Morse code character


  Paramter list:
  char myChar       The character to be sent

  Return value:
  void
*****/
void Send(char myChar)
{
  int index;

  if (isalpha(myChar)) {
    if (islower(myChar)) {
      myChar = toupper(myChar);
    }
    SendCode(letterTable[myChar - 'A']);   // Make into a zero-based array index
    return;
  } else if (isdigit(myChar)) {
    SendCode(numberTable[myChar - '0']);   // Same deal here...
    return;
  }
  index = (int) myChar;
  switch (myChar) {                 // Non-aalpha and non-digit characters
    case '\r':
    case '\n':
    case '!':
      SendCode(0b01101011);         // exclamation mark 33
      break;
    case '"':
      SendCode(0b01010010);         // double quote 34
      break;
    case '$':
      SendCode(0b10001001);         // dollar sign 36
      break;
    case '@':
      SendCode(0b00101000);         // ampersand 38
      break;
    case '\'':
      SendCode(0b01011110);         // apostrophe 39
      break;

    case '(':
    case ')':
      SendCode(0b01011110);         // parentheses (L) 40, 41
      break;

    case ',':
      SendCode(0b01110011);         // comma 44
      break;

    case '.':
      SendCode(0b01010101);         // period  46
      break;
    case '-':
      SendCode(0b00100001);         // hyphen 45
      break;
    case ':':
      SendCode(0b01111000);         // colon 58
      break;
    case ';':
      SendCode(0b01101010);         // semi-colon 59
      break;
    case '?':
      SendCode(0b01001100);         // question mark 63
      break;
    case '_':
      SendCode(0b01001101);         // underline 95
      break;

    case '⌠':
      SendCode(0b01101000);         // paragraph
      break;

    default:
      WordSpace();
      break;
  }
}

/*****
  Purpose: display a character on the LCD display.

  Parameter list:
    char s[]         array that holds chars to display

  Return value:
    void
*****/
void ShowChar(char s)
{
  static int index = 0;

  if (displayState == OFF)              // They don't want to see letters on display
    return;

  M5.Lcd.print(s);

}

/*****
  Purpose: establish the dit length for code transmission. Crucial since
    all spacing is done using dit length

  Parameter list:
    int wpm

  Retrun value:
    void
*****/

void SetDitLength(int wpm)
{
  if (wpm == 0)
    wpm = 15;

  if (encodingType == NORMALENCODING)
  {
    ditlen = 1200 / wpm;
  } else
  {
    ditlen = 1200 / wpm;                  // Change later for Farnsworth...
  }

}

/*****
  Purpose: display a letters on the LCD display and send them in code

  Parameter list:
    void

  Return value:
    void

  CAUTION: assumes call[] is large enough for up to 7 chars
*****/
// ||||||||||||||||||||||||||||
void SendLetters(Menuing menu)
{
  char c;
  int letterCount = 0;
  int rowCount = 0;


  // *****menu.eraseMenus(tft);
  menu.eraseMenus();

 M5.Lcd.setCursor(0, TOPDEADSPACE + 10);
  //while (digitalRead(ENCODERSWITCH1) != LOW)
  // BtnA serves as the encoder's SPST momentary switch
  // pulled up and asserted low
  while (!M5.BtnA.read())
  {
    c = (char) random(0, 26) + 'A';     // Convert to ASCII
    Send(c);
    M5.Lcd.print(c);
    M5.Lcd.print(" ");
    letterCount += 2;     // The space also counts as a letter
    LetterSpace();

    if (letterCount > LETTERSPERROW) {
      rowCount++;
      letterCount = 0;
      if (rowCount > ROWCOUNT) {
        // *****menu.eraseMenus(tft);
        menu.eraseMenus();
        M5.Lcd.setCursor(0, TOPDEADSPACE + 10);
        rowCount = 0;
      }
    }
  }
}
// ||||||||||||||||||||||||||||

/*****
  Purpose: display a letters on the LCD display and send them in code

  Parameter list:
    Menuing menu    the menu object controlling the selections

  Return value:
    void

  CAUTION: assumes call[] is large enough for up to 7 chars
*****/
// ||||||||||||||||||||||||||||
void SendNumbers(Menuing menu)
{
  char c;
  int letterCount = 0;
  int rowCount = 0;

  // *****menu.eraseMenus(tft);
  menu.eraseMenus();
  M5.Lcd.setCursor(0, TOPDEADSPACE + 10);
  //while (digitalRead(ENCODERSWITCH1) != LOW)
  while (!M5.BtnA.read())
  {
    c = (char) random(0, 10) + '0';     // Convert to ASCII
    Send(c);
    M5.Lcd.print(c);
    M5.Lcd.print(" ");
    letterCount += 2;     // The space also counts as a letter
    LetterSpace();

    if (letterCount > LETTERSPERROW) {
      rowCount++;
      letterCount = 0;
      if (rowCount > ROWCOUNT) {
        // *****menu.eraseMenus(tft);
        menu.eraseMenus();
        M5.Lcd.setCursor(0, TOPDEADSPACE + 10);
        rowCount = 0;
      }
    }
  }
}
// ||||||||||||||||||||||||||||

/*****
  Purpose: Send a random sequence of words from a list of words

  Parameter list:
    void

  Return value:
    void
*****/
// ||||||||||||||||||||||||||||
void SendWords(Menuing menu)
{
  char *ptr;
  int letterCount = 0;
  int count;
  int rowCount = 0;
  int index;

  count = 23;
  // *****menu.eraseMenus(tft);
  menu.eraseMenus();
  M5.Lcd.setCursor(0, TOPDEADSPACE);
  //while (digitalRead(ENCODERSWITCH1) != LOW)
  while (!M5.BtnA.read()) // is button A pressed, asserted low)
  {
    index = random(0, count);
    ptr = words[index];
    while (*ptr) {
      ShowChar(*ptr);
      Send(*ptr++);
      letterCount++;
    }
    M5.Lcd.print(" ");
    letterCount++;
    if (letterCount > LETTERSPERROW - 8) {
      rowCount++;
      M5.Lcd.print('\n');
      letterCount = 0;
      if (rowCount > ROWCOUNT) {
        MyDelay(200UL);
        // *****menu.eraseMenus(tft);
        menu.eraseMenus();
        M5.Lcd.setCursor(0, TOPDEADSPACE);
        rowCount = 0;
      }
    }
    WordSpace();
  }
}
// ||||||||||||||||||||||||||||


/*****
  Purpose: Send a random sequence of letters and numbers

  Parameter list:
    Menuing menu

  Return value:
    void
*****/
// ||||||||||||||||||||||||||||
void SendLettersAndNumbers(Menuing menu)
{
  char c;
  int letterCount = 0;
  int rowCount = 0;

  // *****menu.eraseMenus(tft);
  menu.eraseMenus();
  M5.Lcd.setCursor(0, TOPDEADSPACE + 10);
  //while (digitalRead(ENCODERSWITCH1) != LOW)
  while (!M5.BtnA.read()) // is button A pressed, asserted low)
  {
    c = (char) random(48, 90);
    if (c > '9' && c < 'A') {       // Is it out of range for number or letter?
      continue;                     // Yep
    }
    Send(c);
    M5.Lcd.print(c);
    M5.Lcd.print(" ");
    letterCount += 2;               // The space also counts as a letter
    LetterSpace();

    if (letterCount > LETTERSPERROW) {
      rowCount++;
      letterCount = 0;
      if (rowCount > ROWCOUNT) {
        // *****menu.eraseMenus(tft);
        menu.eraseMenus();
        M5.Lcd.setCursor(0, TOPDEADSPACE + 10);
        rowCount = 0;
      }
    }
  }
}
// ||||||||||||||||||||||||||||

/*****
  Purpose: display punctuation characters

  Parameter list:
    Menuing menu    the menu object controlling the selections

  Return value:
    void

  CAUTION: assumes call[] is large enough for up to 7 chars
*****/
// ||||||||||||||||||||||||||||
void SendPunctuation(Menuing menu)
{
  char c;
  int letterCount = 0;
  int rowCount = 0;

  // *****menu.eraseMenus(tft);
  menu.eraseMenus();
  M5.Lcd.setCursor(0, TOPDEADSPACE + 10);
  //while (digitalRead(ENCODERSWITCH1) != LOW)
  while (!M5.BtnA.read()) // is button A pressed, asserted low)
  {
    c = random(0, 14);     // ASCII range for punctuation marks indexes into array
    //    Send(ASCIIForPunctuation[c]);
    SendCode(punctuationTable[c]);
    M5.Lcd.print((char) ASCIIForPunctuation[c]);
    M5.Lcd.print(" ");
    letterCount += 2;     // The space also counts as a letter
    LetterSpace();

    if (letterCount > LETTERSPERROW) {
      rowCount++;
      letterCount = 0;
      if (rowCount > ROWCOUNT) {
        // *****menu.eraseMenus(tft);
        menu.eraseMenus();
        M5.Lcd.setCursor(0, TOPDEADSPACE + 10);
        rowCount = 0;
      }
    }
  }
}
// ||||||||||||||||||||||||||||


/*****
  Purpose: display punctuation characters

  Parameter list:
    Menuing menu    the menu object controlling the selections

  Return value:
    void

  CAUTION: assumes call[] is large enough for up to 7 chars
*****/
// ||||||||||||||||||||||||||||
void SendFieldDay(Menuing menu)
{
  char c;
  int letterCount = 0;
  int rowCount = 0;

  // *****menu.eraseMenus(tft);
  menu.eraseMenus();
  M5.Lcd.setCursor(0, TOPDEADSPACE + 10);
  //while (digitalRead(ENCODERSWITCH1) != LOW)
  while (!M5.BtnA.read()) // is button A pressed, asserted low)
  {
    c = random(0, 14);     // ASCII range for punctuation marks indexes into array
    //    Send(ASCIIForPunctuation[c]);
    FieldDayExcahange();
    //M5.Lcd.print((char) ASCIIForPunctuation[c]);
    //M5.Lcd.print(" ");
    //letterCount += 2;     // The space also counts as a letter
    //LetterSpace();

    /*
      if (letterCount > LETTERSPERROW)
      {
      rowCount++;
      letterCount = 0;
      if (rowCount > ROWCOUNT) {
       // *****menu.eraseMenus(tft);
       menu.eraseMenus();
       M5.Lcd.setCursor(0, TOPDEADSPACE + 10);
       rowCount = 0;
      }
      } */
  }

}
// ||||||||||||||||||||||||||||

/*****
  Purpose: Function generates and send random call signs

  Parameter list:
    Menuing menu    the menu object controlling the selections

  Return value:
    void

  CAUTION: assumes call[] is large enough for up to 7 chars
*****/
// ||||||||||||||||||||||||||||
void DoCallSigns(Menuing menu)
{
  // TODO using polling, must wait for call to be sent before
  // you can exit
  char bogusCall[10];
  int i;
  int letterCount = 0;
  int rowCount = 0;

  // *****menu.eraseMenus(tft);
  menu.eraseMenus();
  M5.Lcd.setCursor(0, TOPDEADSPACE + 10);
  //while (digitalRead(ENCODERSWITCH1) != LOW)
  while (!M5.BtnA.read()) // is button A pressed, asserted low)
  {
    // *****menu.eraseMenus(tft);
    menu.eraseMenus();
    M5.Lcd.setCursor(0, TOPDEADSPACE + 10);
    //while (digitalRead(ENCODERSWITCH1) != LOW)
    while (!M5.BtnA.read()) // is button A pressed, asserted low)
    {
      GenerateDomesticCall(bogusCall);
      i = 0;
      while (bogusCall[i]) {
        Send(bogusCall[i]);
        M5.Lcd.print(bogusCall[i++]);
        letterCount++;     // The space also counts as a letter
        LetterSpace();
      }
      M5.Lcd.print(", ");
      letterCount += 2;     // The space also counts as a letter
      if (letterCount > LETTERSPERROW - 5) {
        rowCount++;
        M5.Lcd.print('\n');
        letterCount = 0;
        if (rowCount > ROWCOUNT) {
          // *****menu.eraseMenus(tft);
          menu.eraseMenus();
          M5.Lcd.setCursor(0, TOPDEADSPACE + 10);
          rowCount = 0;
        }
      }
    }
    GenerateDomesticCall(bogusCall);
  }
}
// ||||||||||||||||||||||||||||
/*****
  Purpose: to send a Morse code dit

  Paramter list:
  void

  Return value:
  void

  CAUTION: Assumes that a global named ditlen holds the value for dit spacing
*****/
void DoQSO(Menuing menu)
{
  char c[2];
  char temp[10];
  char QSO[300];
  int restore;
  long myRand;
  int randi;


  restore = encodingType;
  encodingType = NORMALENCODING;
  randomSeed(millis());

  //menu.eraseMenus(tft);
  menu.eraseMenus();
  //tft.setCursor(0, TOPDEADSPACE + 10);
  M5.Lcd.setCursor(0, TOPDEADSPACE + 10);
  GenerateDomesticCall(fake);   // Add their call

  strcpy(QSO, fake);
  strcat(QSO, " ");
  strcat(QSO, words[0]);        // Get "DE"
  strcat(QSO, " ");

  randi = rand();

  if (randi % 2L == 0)
    strcat(QSO, MYCALL);          // Your call sign from header file
  else
    strcat(QSO, MYCALL_);          // Your call sign from header file

  strcat(QSO, ". ");
  strcat(QSO, words[1]);        // Get "TNX FER"
  strcat(QSO, " ");

  myRand = random(0, 10);
  if (myRand % 2L == 0)
    strcat(QSO, words[24]);      // Get "CALL"
  else
    strcat(QSO, words[21]);      // Get "RPT"

  strcat(QSO, " ");
  myRand = random(0, 10);
  if (myRand % 2L == 0)
    strcat(QSO, words[26]);      // Get "SLD"
  else
    strcat(QSO, words[27]);      // Get "FB"
  strcat(QSO, " ");
  strcat(QSO, words[13]);       // Get "CPI"
  strcat(QSO, ". ");
  strcat(QSO, words[25]);       // Get "UR"
  strcat(QSO, " ");
  strcat(QSO, words[28]);       // Get "RST"
  strcat(QSO, " ");

  myRand = random(3, 6);        // Generate RST
  c[0] = myRand + '0';
  c[1] = '\0';
  strcat(QSO, c);               // 'R'
  myRand = random(6, 10);
  c[0] = myRand + '0';
  c[1] = '\0';
  strcat(QSO, c);               // 'S'
  strcat(QSO, "9. ");           // 'T'

  strcat(QSO, words[22]);       // "NAME"
  strcat(QSO, " IS ");        // "IS"
  myRand = random(0, 12);
  strcat(QSO, names[myRand]);   // bogus name
  strcat(QSO, ". ");
  strcat(QSO, words[23]);       // "QTH"
  strcat(QSO, " ");
  strcat(QSO, "IS");            // "IS"
  strcat(QSO, " ");

  Serial.println(QSO);
  Serial.println("Level 1");

  myRand = random(0, 13);
  strcat(QSO, cities[myRand]);  // bogus city
  Serial.print("cities[myRand] = ");
  Serial.println(cities[myRand]);

  strcat(QSO, ". ");
  strcat(QSO, words[7]);        // "RIG"
  strcat(QSO, " ");
  strcat(QSO, words[4]);        // "HR"
  strcat(QSO, " ");
  strcat(QSO, "IS");            // "IS"
  strcat(QSO, " ");
  myRand = random(0, 4);
  switch (myRand) {
    case 0:                     // "ICOM"
      strcat(QSO, "ICOM ");
      myRand = random(0, 9);
      break;
    case 1:                     // "KENWOOD"
      strcat(QSO, "KENWOOD ");
      myRand = random(9, 13);
      break;
    case 2:                     // "YAESU"
      strcat(QSO, "YAESU ");
      myRand = random(13, 18);
      break;
    case 3:                     // "ICOM"
      strcat(QSO, "Flex ");
      myRand = random(18, 23);
      break;
  }
  strcat(QSO, rigNumbers[myRand]);
  strcat(QSO, ", ");

  strcat(QSO, words[8]);        // "ANT "
  strcat(QSO, " ");
  myRand = random(0, 4);
  switch (myRand) {
    case 0:
      strcat(QSO, words[9]);        // "DIPOLE"
      break;
    case 1:
      strcat(QSO, words[10]);       // "VERTICAL"
      break;
    case 2:
      strcat(QSO, words[11]);       // "BEAM"
      break;
    case 3:
      strcat(QSO, words[29]);        // "EFHW"
      break;
  }
  strcat(QSO, ". ");
  strcat(QSO, words[3]);        // "WX"
  strcat(QSO, " ");
  strcat(QSO, "IS ");            // "IS"

  myRand = random(0, 7);
  switch (myRand) {
    case 0:
      strcat(QSO, words[14]);        // "WARM"
      break;
    case 1:
      strcat(QSO, words[15]);       // "SUNNY"
      break;
    case 2:
      strcat(QSO, words[16]);       // "CLOUDY"
      break;
    case 3:
      strcat(QSO, words[17]);        // "COLD"
      break;
    case 4:
      strcat(QSO, words[18]);        // "RAIN"
      break;
    case 5:
      strcat(QSO, words[19]);        // "SNOW"
      break;
    case 6:
      strcat(QSO, words[20]);        // "FOG"
      break;
  }
  strcat(QSO, ". ");
  strcat(QSO, words[12]);             // "HW"
  strcat(QSO, " ");
  strcat(QSO, words[13]);             // "CPI"
  strcat(QSO, "?");                   // "?"
  strcat(QSO, " ");
  strcat(QSO, fake);                // My call
  strcat(QSO, " ");
  strcat(QSO, words[0]);              // "DE"
  strcat(QSO, " ");


  if (randi % 2L == 0)
    strcat(QSO, MYCALL);          // Your call sign from header file
  else
    strcat(QSO, MYCALL_);          // Your call sign from header file

  strcat(QSO, "KN");

  Serial.println(QSO);
  ShowString(QSO);
  encodingType = restore;


}

/*****
  Purpose: This function reads the dit and dah paddles and decodes the characters

  Paramter list:
    Menuing menu        the menuing object

  Return value:
  void

*****/
// ||||||||||||||||||||||||||||
void Listen(Menuing menu)
{
  char pattern[10];
  int index;
  unsigned long start, end;
  unsigned long gap;
  float spacing = 5.0 * wordsPerMinute;   // 5 characters per word
  spacing = 60.0 / spacing;               // how many seconds per character
  gap = (long) (spacing * 1000.0);        // milliseconds
  gap *= 3UL;                               // pause between characters

  Serial.print("gap = ");
  Serial.println(gap);
  index = 0;
  start = millis();

  // *****menu.eraseMenus(tft);
  menu.eraseMenus();
  M5.Lcd.setCursor(0, TOPDEADSPACE + 10);

  //while (digitalRead(ENCODERSWITCH1) != LOW)
  while (!M5.BtnA.read()) // is button A pressed, asserted low)
  { // Are they done?
    //if (digitalRead(DITPADDLE) == LOW)
    if (digitalRead(DITPADDLE) == LOW)
    { // Paddle dit?
      Serial.println("In dit");
      pattern[index++] = '.';
      dit();
    }
    if (digitalRead(DASHPADDLE) == LOW) {           // Paddle dah
      Serial.println("In dah");
      pattern[index++] = '-';
      dah();
    }

    if (millis() - start > gap + 200) {
      pattern[index] = '\0';                  // Make it a string
      Serial.print("pattern = ");
      Serial.println(pattern);
      index = Decode(pattern);
      Serial.print("index = ");
      Serial.println(index);
      if (index > 63) {
        Serial.println("Is punctuation");
      } else {
        if (myReverseBinarySearchSet[index] != '#')
          M5.Lcd.print(myReverseBinarySearchSet[index]);
      }
      index = 0;
      start = millis();
    }
  }
}
// ||||||||||||||||||||||||||||
/*****
  Purpose: To perform a binary search on the pattern strong of dit and dah to find the
      corresponding letter.

  Parameter list:
    char *s        the input pattern string to use for the search

  Return value:
    int            an index into the search set character array.

*****/
int Decode(char *s)
{
  static int num = 0;

  num = 1;              // Set the sentinel...
  while (*s) {          // More characters??
    num = num << 1;     // Yep, so shift what we have left one bit
    if (*s++ == '.') {  // Are we looking at a dit?
      num++;            //         Yep...add 1
    }                   //         Nope, leave it a 0
  }
  return num;           // We're done, shove num in the backpack and go home
}

/*****
  Purpose: Send a random call and wait for user to send it back. If incorrect, pass error code, otherwise return.

  Paramter list:
    Menuing menu        the menu object

  Return value:
    void

*****/
void DoCopyCat(Menuing menu)
{
  char c;
  char pattern[10];
  char input[10];
  char response[10];
  int i, index, letterIndex;
  unsigned long start;
  unsigned long gap;

  float spacing = 5.0 * wordsPerMinute;       // 5 characters per word, spacing = letters per minut
  spacing = 60.0 / spacing;                   // how many seconds per character
  gap = (unsigned long) (spacing * 1000.0);   // milliseconds/character

  i = index = 0;

  // *****menu.eraseMenus(tft);
  menu.eraseMenus();
  M5.Lcd.setCursor(0, TOPDEADSPACE + 10);

  pattern[0] = response[0] = input[0] = '\0';
  letterIndex = index = 0;
  while (true) {                                    // Spin around forever
    //if (digitalRead(ENCODERSWITCH1) == LOW)
    if (!M5.BtnA.read())
    { // They want to leave
      return;
    }
    GenerateDomesticCall(pattern);                  // Create random call sign'
    while (pattern[i]) {                            // Send call
      Send(pattern[i++]);
      start = millis();                             // Start timer
    }

    while (true)
    {
      // We have a call, now wait for a send-back
      //if (digitalRead(ENCODERSWITCH1) == LOW)
      if (!M5.BtnA.read())
      { // They've had enough...we're outta here...
        return;
      }
      if (digitalRead(DITPADDLE) == LOW) {            // Paddle dit?
        input[index++] = '.';
        dit();
        start = millis();                             // Start timer
      }
      if (digitalRead(DASHPADDLE) == LOW) {           // Paddle dah
        input[index++] = '-';
        dah();
        start = millis();                             // Start timer
      }

      if (millis() - start > ditlen) {           // End a letter?
        input[index] = '\0';                          // Make it a string
        index = Decode(input);
        c = myReverseBinarySearchSet[index];
        if (c != '#') {
          response[letterIndex++] = c;
          M5.Lcd.print((char) c);
        }
        index = 0;
        input[0] = '\0';
      }
      if (millis() - start > gap * 7UL) {
        break;
      }
    }

    if (millis() - start > gap * 3UL) {
      response[letterIndex] = '\0';
      if (strcmp(response, pattern) == 0) {     // Did user match call?
        M5.Lcd.print(" GOOD!\n");
      } else {
        M5.Lcd.print(" ?\n");
      }
      MyDelay(2000UL);
      input[0]    = '\0';
      response[0] = '\0';
      pattern[0]  = '\0';
      i = letterIndex = index = 0;
    }
  }
}


/*****
  Purpose: Send a random character and, after a Farnsworth delay, show the character in large font

  Paramter list:
    char *s        the input pattern string to use for the search

  Return value:
    int            an index into the search set character array.

*****/
// ||||||||||||||||||||||||||||
void DoFlashCard(Menuing menu)
{
  char c;
  char asciiEquivalent;
  int index;
  int row, col;
  long rand;

  randomSeed(millis());                 // Re-seed pseudo-random number generator

  M5.Lcd.setTextSize(7);
  M5.Lcd.setTextColor(GREEN, BLACK);

  row = DISPLAYHEIGHT / 2 - 30;
  col = DISPLAYWIDTH / 2 - 20;

  //while (digitalRead(ENCODERSWITCH1) != LOW)
  while (!M5.BtnA.read()) // is button A pressed, asserted low)
  {
    // *****menu.eraseMenus(tft);
    menu.eraseMenus();
    M5.Lcd.setCursor(col, row);
    rand = random(0, 3);                // Letters, numbers, punctuation??
    switch (rand) {
      case 0:                           // Letters
        index = (int) random(0, 26);    // Create index into letter array
        c = letterTable[index];
        asciiEquivalent = index + 'A';
        break;
      case 1:                           // Numbers
        index = (int) random(0, 10);
        c = numberTable[index];
        asciiEquivalent = index + '0';
        break;
      case 2:                           // Punctuation
        index = (int) random(0, 15);
        c = punctuationTable[index];
        asciiEquivalent = ASCIIForPunctuation[index];
        break;
    }
    SendCode(c);
    MyDelay(ditlen * 100 / FARNSWORTHSTART);
    M5.Lcd.print(asciiEquivalent);
    M5.Lcd.print(" ");
    MyDelay(FLASHCARDVIEWDELAY);
  }
  M5.Lcd.setTextSize(2);       // 26 characters per line
  M5.Lcd.setTextColor(GREEN, BLACK);


}
// ||||||||||||||||||||||||||||
