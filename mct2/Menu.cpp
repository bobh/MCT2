#ifndef BEENHERE
#include "MorseTutor.h"
#endif



/****
  Purpose: This is the constructor for the menuing system.

  Parameter list:
    int displayWidth     the max width for this menu
    int menuLevels       what it the depth of the menus
    unit16 foreColor        display menu item in this fore color...
    unit16 backColor        ...using this background color
    unit16 activeFore       Highlight active menu choice with this fore color...
    unit16 activeBack       ...and this back color
    int font             using this font size

  Return value:
    void
*****/
Menuing::Menuing(int displayWidth, int displayHeight, int foreColor, int backColor, int activeFore, int activeBack, int font)
{
  width                 = displayWidth;
  height                = displayHeight;
  foregroundColor       = foreColor;        // Unselected
  backgroundColor       = backColor;
  selectForegroundColor = activeFore;       // Selected
  selectBackgroundColor = activeBack;
  fontSize              = font;
}


/*****
  Purpose: To show a menu option

  Paramter list:
    const char *whichMenu[]     // Array of pointers to the menu option
    int len;                    // The number of menus

  Return value:
    void
*****/

// *****
void Menuing::showMenu(char *whichMenu[])
{
  int i;
  
  M5.Lcd.setTextColor(foregroundColor, backgroundColor);
  activeRow = 0;
  for (i = 0; i < itemCount; i++) {
    M5.Lcd.setCursor(i * spacing, activeRow);
    M5.Lcd.print(whichMenu[i]);
  }
  activeColumn = activeMenuIndex * spacing;

  M5.Lcd.setCursor(activeColumn, activeRow);
  M5.Lcd.setTextColor(selectForegroundColor, selectBackgroundColor);
  M5.Lcd.print(whichMenu[activeMenuIndex]);
}



/*****
  Purpose: To erase all sub menus while leaving the top-most menu unchanged

  Parameter list:

  Return value:
    void
*****/

void Menuing::eraseMenus()
{
  // ****** myDisplay.fillRect(0, TOPDEADSPACE, DISPLAYWIDTH, DISPLAYHEIGHT, BLACK);   // Erase old speed line
  M5.Lcd.fillRect(0, TOPDEADSPACE, DISPLAYWIDTH, DISPLAYHEIGHT, BLACK);
}

/*****
  Purpose: To erase all sub menus while leaving the top-most menu unchanged

  Parameter list:

  Return value:
    void
*****/

void Menuing::eraseDisplay()
{
  M5.Lcd.fillRect(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT, BLACK);   // Erase old speed line
}
/*****
  Purpose: This presents a new submenu, displays it, and waits for a choice

  Parameter list:
    int activeMenuLevel     the current menu level
    char *menu[]            the menu choices
    int orientation         horizontal or dropdown

  Return value:
    int                     the choice selected
*****/

void Menuing::deselectMenuItem(char *menu[])
{

  int col, row;
  col = activeMenuIndex * spacing;

  if (activeMenuLevel == 0) 
  {
    row = 0;                                  // Start below top menu and work down
    activeRow = row;
    activeColumn = col;                                // Where is top-most column?
  } else 
  {
    col = spacing * activeMenuIndex;
    row = ROWSPACING * activeMenuIndex;
  }
  M5.Lcd.setTextColor(foregroundColor, backgroundColor);
  M5.Lcd.setCursor(col, row);                // Put on old choice...
  M5.Lcd.print(menu[activeMenuIndex]);       // ...and de-select it.
  
}

/*****
  Purpose: This moves to the next menu item

  Parameter list:
    char *menu[]         pointer to the current menu list
    int encoder          direction of rotation

  Return value:
    int                 currently active index
*****/


int Menuing::updateMenu(char *menu[], int encoder)
{
  int col, row;

  if (encoder == 1)             // Based on encoder movement...
    activeMenuIndex++;          // ...advance to next item, or...
  else
    activeMenuIndex--;          // ...backup to previous item

  if (activeMenuIndex > itemCount - 1) // Advanced too far, set to first item
    activeMenuIndex = 0;
  if (activeMenuIndex < 0)                                    // Backed up too far, set to end item
    activeMenuIndex = itemCount - 1;

  col = activeMenuIndex * spacing;
  activeColumn = col;
  if (activeMenuLevel == 0) {
    row = ROWSPACING * activeMenuLevel;           // Upper most menu always goes on first line
  } else {
    row = TOPDEADSPACE + ROWSPACING * activeMenuIndex;
  }
  activeRow = row;

  M5.Lcd.setTextColor(selectForegroundColor, selectBackgroundColor);
  M5.Lcd.setCursor(col, row);
  M5.Lcd.print(menu[activeMenuIndex]);
  return activeMenuIndex;
}
/*****
  Purpose: This displays a new submenu

  Parameter list:
    int activeMenuLevel     the current menu level
    char *menu[]            the menu choices
    int itemCount           the number of choices in this menu
    int orientation         horizontal or dropdown
    int defaultIndex        which menu choice is the default?

  Return value:
    int                     the default menu selection
*****/



/*****
  Purpose: This presents a new menu depending upon the encoder direction
  Parameter list:
    char *menu           pointer to the current menu list
    int whichLevel       the setup is for this menu
    int encoder          direction of rotation
    Menuing mine         the menu being used
    int defaults[]       the array that tells which element of the menu is the default

  Return value:
    int                  the default option being presented
*****/



void Menuing::showNewMenu(char *menu[], int encoder, int defaults[])
{
  int col, i, row;
           
  activeColumn = col = spacing * activeMenuIndex;         // Start at main menu column

  for (i = 0; i < itemCount; i++) {
    row = TOPDEADSPACE + ROWSPACING * i;              // Start below top menu and work down
    if (i == defaults[activeMenuIndex]) {
      M5.Lcd.setTextColor(selectForegroundColor, selectBackgroundColor);          // All others are unselected
      defaultOption = defaults[activeMenuIndex];            // This is the currently-active menu selection
      activeRow       = row;
      activeColumn    = col;
    } else {
      M5.Lcd.setTextColor(foregroundColor, backgroundColor);          // All others are unselected
    }
    M5.Lcd.setCursor(col, row);
    M5.Lcd.print(menu[i]);
  }
  MyDelay(500UL);
  activeMenuIndex = defaultOption;
}

/*****
  Purpose: This scrolls the top-most menu horizontally

  Parameter list:
    Adafruit_ILI9341 myDisplay    display object
    char *menu[]                  pointer to menu options
    int encoder                   direction of rotation
    int defaults[]       the array that tells which element of the menu is the default

  Return value:
    void
*****/


// *****
void Menuing::scrollTopMenu(char *menu[], int encoder, int defaults[])
{

  if (encoder == 1)             // Based on encoder movement...
    activeMenuIndex++;          // ...advance to next item, or...
  else
    activeMenuIndex--;          // ...backup to previous item

  if (activeMenuIndex > itemCount - 1) // Advanced too far, set to first item
    activeMenuIndex = 0;
  if (activeMenuIndex < 0)                                    // Backed up too far, set to end item
    activeMenuIndex = itemCount - 1;

  activeColumn = col = activeMenuIndex * spacing;
  activeRow    = row = 0;           // Upper most menu always goes on first line

  M5.Lcd.setTextColor(selectForegroundColor, selectBackgroundColor);
  M5.Lcd.setCursor(col, row);
  M5.Lcd.print(menu[activeMenuIndex]);
}
/*****
  Purpose: This scrolls the top-most menu horizontally

  Parameter list:
    Adafruit_ILI9341 myDisplay    the tft display
    char *menu                    pointer to the current menu list
    Menuing mine                  the menu being used

  Return value:
    int                   the submenu choice made
*****/

//  The rotary encoder specified is equiped with a switch "ENCODERSWITCH1".
//  Contact PUSH ON momentary SPST
//  Asserted LOW
//  We will use Button A for this function

int Menuing::selectFromMenu( char *menu[])
{
  static int val = 1; // I'm going too far in keeping the old code
                      // but I started and now in too deep!

  activeMenuIndex = defaultOption;
 
  //while (digitalRead(ENCODERSWITCH1) != LOW) 
  while( M5.BtnA.read()  )   
  {

    dir = ReadEncoder();
    
    if (dir) {
      if (dir == 1)
      {
        //val++;
        val = 2;// Clockwise          (CW)
      }
      else
      {
        //val--;                      // Counter-clockwise  (CCW)
        val = -2;
      }
      if (val == 2 || val == -2) {  // It takes 2 pulses to make a rotation
        
        M5.Lcd.setTextColor(foregroundColor, backgroundColor);    // Turn off current option
        M5.Lcd.setCursor(activeColumn, activeRow);
        M5.Lcd.print(menu[activeMenuIndex]);      
                                                  // Find next option...
        if (val > 0) {                            // CW??
          activeMenuIndex++;
        } else {                                  // Nope, CCW
          activeMenuIndex--;
        }
        if (activeMenuIndex > itemCount - 1) // Advanced too far, set to first item
          activeMenuIndex = 0;
        if (activeMenuIndex < 0)                                  // Backed up too far, set to end item
          activeMenuIndex = itemCount - 1;

        activeRow = TOPDEADSPACE + ROWSPACING * activeMenuIndex;  // Determine active row

        M5.Lcd.setTextColor(selectForegroundColor, selectBackgroundColor);
        M5.Lcd.setCursor(activeColumn, activeRow);
        M5.Lcd.print(menu[activeMenuIndex]);

        val = 1;
      }
    }
  }

  return activeMenuIndex;
}
