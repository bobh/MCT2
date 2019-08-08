#ifndef BEENHERE
#include "MorseTutor.h"
#endif

#ifndef MENU
#define MENU

#define HORIZONTAL       1    // Menu orientation
#define DROPDOWN         2

#define MAXMENUDEPTH    10
#define MENURANK        10     // The max level of menus



class Menuing
{
  public:
    int itemCount;              // options in a menu
    int defaultOption;          // which is highlighted when shown. Taken from defaultsList[] array
    int width;                  // width of display  (340)
    int height;                 // height of display (240)
    int spacing;                // pixel count available for each main menu option
    int activeColumn;           // Which column is active
    int activeRow;              // Which row is active
    int fontSize;               // Default text size
    int foregroundColor;        // Color of normal text
    int backgroundColor;        // Background color
    int selectForegroundColor;  // Color for active menu option
    int selectBackgroundColor;  // Background color for all menus
  
    //void deselectMenuItem(Adafruit_ILI9341 myDisplay, char *menu[]);
    //void eraseDisplay(Adafruit_ILI9341 tft);
    //void eraseMenus(Adafruit_ILI9341 tft);
    // **********
    void eraseMenus();
    void eraseDisplay();
    void showMenu(char *whichMenu[]);
    void deselectMenuItem(char *menu[]);
    void scrollTopMenu(char *menu[], int encoder, int defaults[]);
    int  updateMenu(char *menu[], int encoder);
    void showNewMenu(char *menu[], int encoder, int defaults[]);
    int  selectFromMenu(char *menu[]);
    
    Menuing(int displayWidth, int displayHeight, int foreColor, int backColor, int activeFore, int activeBack, int font);
    //void scrollTopMenu(Adafruit_ILI9341 myDisplay, char *menu[], int encoder, int defaults[]);
    //int  selectFromMenu(Adafruit_ILI9341 myDisplay, char *menu[]);
    //void showMenu(Adafruit_ILI9341 myDisplay, char *whichMenu[]);
    //int  showMenuLevel(Adafruit_ILI9341 myDisplay, char *menu, int itemCount, int orientation,  int defaultIndex);
    //void showNewMenu(Adafruit_ILI9341 myDisplay, char *menu[], int encoder, int defaults[]);
    //int  updateMenu(Adafruit_ILI9341 myDisplay, char *menu[], int encoder);
    
    
  private:
  
};

extern Menuing myMenu;
#endif
