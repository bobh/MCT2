#ifndef BEENHERE
#define BEENHERE

// #define DEBUG_                       // Uncomment when debugging

#define VERSION   007               // Version number
#define SUBVERSION   "Community-001-M5Stack" // Version number
#define MYCALL  "W8TEE"             // Change to your call
#define MYCALL_  "WM6H"             // Change to your call

//#include <avr/pgmspace.h>
#include <stdint.h>
// ****#include <SPI.h>ILI9341
#include <SPI.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_ILI9341.h>
//#include <Adafruit_MCP4725.h>
//#include <Fonts/FreeSerif9pt7b.h>
//#include <Fonts/FreeSerif12pt7b.h>
//#include <Fonts/FreeSerif18pt7b.h>
#include <Wire.h>                 // Standard with IDE
//#include <Rotary.h>               // https://github.com/brianlow/Rotary
//#include <Time.h>                 //https://github.com/PaulStoffregen/Time
//#include <TimeLib.h>
//#include <Tone.h>
//#include <EEPROM.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Menu.h"                   // This is our header

#include <stdint.h>

#include <M5Stack.h>

#define ELEMENTS(x) (sizeof(x) / sizeof(x[0]))


#define EEPROM_SIZE 64

// This is our header



//======================================= Pin Assignments ==================================

/*                                    Display Pins
  Display wiring:
    Display       STM32f103
   SDO/MISO         A6
      LED           Vcc (3.3V)
      SCK           A5  
   SDI/MOSI         A7
    DC/RS           A0
    RESET           Vcc via a 10K resistor
      CS            A1
     GND            GND
     Vcc            3.3V
*/
// For the Adafruit shield, these are the default pins.
// **** todo assign pins
/*
#define SPEAKERPIN        PA2     //For sidetone

#define ENCODER1PINA      PA8     //Encoder1
#define ENCODER1PINB      PA9     //Encoder1
#define ENCODERSWITCH1   PB15     //Encoder1

#define DASHPADDLE        PB7     // tip
#define DITPADDLE         PB8     // ring
*/
// pin 25 is ESP32 DAC#1 and connected to the M5Stack speaker
#define SPEAKERPIN        25     //For sidetone
#define EXT_SPEAKER       26     // DAC2 for external speaker

#define TEST_PIN          17

#define ENCODER1PINA      8     //Encoder1
#define ENCODER1PINB      9     //Encoder1
#define ENCODERSWITCH1   15     //Encoder1

#define DASHPADDLE        2     // tip
#define DITPADDLE         5     // ring

// ====================================== Display Constants ================================
#define DISPLAYWIDTH      320
#define DISPLAYHEIGHT     240
#define TOPDEADSPACE       30     // All dropdown submenus appear below top line which never disappears
#define ROWSPACING         25     // Pixel count between rows
#define LETTERSPERROW      27
#define ROWCOUNT           10     // number of rows that can be displayed on a page

//======================================= Menu Constants ===================================
#define FIRSTOFFSET         0     // Offsets are used to generate a unique menu number by adding the offset to activeMenuIndex
#define SECONDOFFSET      100
#define THIRDOFFSET       200

#define RECEIVESTATE        1
#define SENDSTATE           2
#define CONFIGURATIONSTATE  3

//======================================  Color Constants =================================
// NOTE: If you try these constants and your display looks weird, try taking the compliment of the colors
//       shown here using the compilment opertor (~, tilde): e.g., BLUE  ~0x001F
// Color definitions
#define BLACK         0x0000
#define BLUE          0x001F
#define RED           0xF800
#define GREEN         0x07E0
#define CYAN          0x07FF
#define MAGENTA       0xF81F
#define YELLOW        0xFFE0
#define WHITE         0xFFFF
#define DKGREEN       0x03E0

#define CW            1
#define CCW          -1

#define ROTARYDELAY        300                  // Milliseconds for display delay

#define WPMOFFSET           10                  // Byte offset in EEPROM for WPM
#define DISPLAYOFFSET       (WPMOFFSET + 1)     // Is display ON or OFF?
#define CALLOFFSET          15                  // Store call in EEPROM
#define WORDOFFSET          30                  // Byte offset in EEPROM to word list
#define MAXWORDLENGTH       10                  // Treat as fixed-field length records.
#define USERNAME            "JACK "             // Note space at end
#define USERQTH             "CINCINNATI, OH "   //        "

#define FREQUENCY          700                  // Sidetone frequency default
#define FREQUENCYINCREMENT  10                  // Number of Hz an encoder detent changes the frequency
#define MAXFREQ           1200                  // Upper limit for sidetone
#define MINFREQ            300                  // Lower        "
#define MAXMSGLENGTH       128                  // Max QSO string length
#define SCREENWIDTH         16                  // Chars on one line of LCD

#define LETTERA             65                  // ASCII codes
#define LETTERZ             90

#define ONELETTERPREFIX       0                 // For generating test call signs
#define TWOLETTERPREFIX       1

#define OFF                   0                 // Used for display state
#define ON                    1

#define ICOMOFFSET            0                 // Where in the array below do the mfg's numbers begin
#define KENWOODOFFSET         9
#define YAESUOFFSET          12
#define FLEXOFFSET           17

//=============================================== CW symbolic constants ====================================================
#define DIT                    1
#define DAH                    2

#define DITMULTIPLIER          1                  // The dit is the basic unit of time
#define DAHMULTIPLIER          3                  // A dah is three times a dit
#define LETTERSPACE           (DITMULTIPLIER * 5)
#define WORDSPACE             (DITMULTIPLIER * 7)
#define USINGKEYER             0                  // This is determined by reading the key jack. If one is grounded, assume straight key
#define USINGSTRAIGHTKEY       1

#define TRANSMITCW            32

#define NORMALENCODING         0                  // Standard encoding
#define FARNSWORTHENCODING     1                  // Requires target and Farnsworth speeds
#define WPMMAX                50
#define WPMMIN                 5
#define GOALSPEED             35                  // The WPM you'd like to reach...eventually!
#define FARNSWORTHSTART       10                  // The starting spacing for WPM
#define FLASHCARDVIEWDELAY 800UL                  // The millisecond delay to show a flashcard character

//========================================== EEPROM Constants =====================
// These are offset addresses from base of EEPROM page
//#define WORDSPERMINUTE      0x00
//#define SIDETONE            0x04
//#define WHICHISDITPADDLE    0x08
//#define FARSWORTHSPEED      0x0C
//#define KOCHSPEED           0x10
//#define ENCODINGACTIVE      0x14


extern float volume;
extern int ditLength;
extern int dahLength;

extern void playTone(unsigned long len);

//typedef   float      FLOAT_32;
//typedef   signed int INT_32;

//extern Rotary r;                                  // sets the pins the rotary encoder uses.  Must be interrupt pins.
//extern Adafruit_ILI9341 tft;
// ***************extern Adafruit_MCP4725 dac;
//extern Rotary myEncoder;
extern Menuing myMenu;

extern int  readKeyPresses();

extern char *menuLevel1[];
extern char *menuReceive[];
extern char *menuSend[];
extern char *menuConfig[];
extern char *names[];
extern char *cities[];

extern char msg[];         // Don't forget the NULL
extern char spaces[];
extern char screen[];
extern char QSO[];
extern char fake[];
extern char letterTable[];
extern char myReverseBinarySearchSet[];
extern char numberTable[];
extern char punctuationTable[];
extern char *words[];
extern char ssClasses[];
extern char *sectionList[];
extern char *states[];
extern char *mainMenu[];
extern char *rigNumbers[];
extern char singleCallSignPrefixes[];
extern char *doubleCallSignPrefixes[];

extern byte WPM;
extern byte displayState;

extern int activeMenuIndex;               // Which menu item is currently selected
extern int activeMenuLevel;               // Which menu level is being used
extern int activeColumn;
extern int activeRow;
extern int ASCIIForPunctuation[];
extern int aVal;
extern int col, row;

extern int old_count;
extern int dir;
extern int ditlen;
//extern uint16_t ditPaddle;
extern int elements;                      // Holds menu elements
extern uint16_t encodingType;               // Normal or Farnsowrth
extern int enState;
extern int farnsworthDelay;
//extern uint16 farnsworthWPM;
extern uint16_t farnsworthWPM;
extern uint16_t kochSpeed;
extern int menuState;                     // Which menu is active
extern int spacing;
extern uint16_t sidetoneFrequency;             
extern int targetWPM;
extern int tutorMode;
extern int defaultsList[];
extern uint16_t wordsPerMinute;

extern volatile int abOld, count, oldCount, rotationDirection;     // + is CW, - is CCW
extern volatile int enc_cnt;

extern void CreateRig(char s[]);

extern char *ltoa(long, char *, int);
extern char *itoa(int, char *, int);

void DefineEEPROMPage();
void FetchWordFromEEPROM(int offset);
void Erase();
void dit();
void dah();
int  Decode(char *s);
void DoCallSigns(Menuing menu);
void DoCopyCat(Menuing menu);
void DoFlashCard(Menuing menu);
void DoQSO(Menuing menu);
void encoder1_read(void);
int  EncoderUpdate(int count);
void EXTI9_5_IRQHandler(void);
void FieldDayExcahange();
void GenerateDomesticCall(char call[]);
void LetterSpace();
void Listen(Menuing menu);
void MyDelay(unsigned long millisWait);
int  ProcessEncoder();
void ReadConfigData();
void ReadDisplayState();
//int8_t ReadEncoder();
int ReadEncoder();
void ReadUserCall(char s[]);
void SaveConfigData();
void SaveEEPROMDefaults();
void SendCode(char code);
void Send(char myChar);
void SetKeyerSpeed();
void SendLetters(Menuing menu);
void SendLettersAndNumbers(Menuing menu);
void SendNumbers(Menuing menu);
void SendPunctuation(Menuing menu);
void SendFieldDay(Menuing menu);
void SendWords(Menuing menu);
void SetDefaults();
void SetDisplayState();
void SetDitLength(int wpm);
int  SetDitPaddle();
int  SetFarnsworthWPM();
int  SetEncodingType();
void SetNewSidetone();
// +++++++++++++++++++++++++++
extern uint16_t setVol();
// +++++++++++++++++++++++++++

int  SetTargetWPM();
void SetWPM();
void ShowChar(char s);
void ShowConfigData();
void ShowCurrentSelection(char *m[], int which);
void ShowString(char s[]);
void ShowSweepStakes();
void ShowCurrentSelection(char *m[], int which);
void WordSpace();
void WriteDisplayState();
int  WriteEEPROMValue(int address, int value);
void WriteWPM();
void WriteWordsToEEPROM();
void WriteUserCall();


#endif
