#ifndef BEENHERE
#include "MorseTutor.h"
#endif

/****

  Purpose: Read the rotary encoder for encoder movement based on econder states

  Parameter list:
    void

  Return value:
    void
*****/
// we subsitute M5Stack buttons for the rotary encoder
// 0 no button pressed, 1 right button, -1 left button

int ReadEncoder()
{
  //static int8_t enc_states[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
  //static uint8_t old_AB = 0;
  /**/
  //old_AB <<= 2;                   //remember previous state
  //old_AB |= (digitalRead(ENCODER1PINB) << 1) | digitalRead(ENCODER1PINA);  //add current state
  //return (enc_states[( old_AB & 0x0f )]);

  int localDir = 0;

  //if (M5.BtnB.pressedFor(10))
  if (M5.BtnB.read())

  {
    localDir = -1; // Button B is CW
  }
  //else if(M5.BtnC.pressedFor(10)) // Button B is CCW
  else if (M5.BtnC.read()) // Button B is CCW
  {
    localDir = 1;
  }
  else
  {
    localDir = 0;
  }

  if (localDir == 1)
  {
    while (M5.BtnC.read())
    { }
  }
  if (localDir == -1)
  {
    while (M5.BtnB.read())
    { }
  }

  return localDir;

}

/*****
  Purpose: Process encoder movement

  Parameter list:
    void

  Return value:
    int             1 on CW, -1 on CCW, 0 on no movement
*****/
/*
  Available from M5Stack
  Button:
  M5.BtnA/B/C. read(); Constantly returns true if the button is pressed and false if pressed
  M5.BtnA/B/C. isPressed(); If the button was pressed – always returns true
  M5.BtnA/B/C. isReleased(); If the button is pressed – always returns true
  M5.BtnA/B/C. wasPressed(); One press – one true
  M5.BtnA/B/C. was released(); One UPS – single true
  M5.BtnA/B/C. pressedFor(uint32_t ms); If the button is pressed more than the set time – always returns true
  M5.BtnA/B/C. releasedFor(uint32_t ms); If the button is pressed more than the set time – always returns true
  M5.BtnA/B/C. lastChange(); Constantly returns true if the button has ever been pressed
*/

int ProcessEncoder()
{
  int8_t result;
  int localDir;
  static int val = 1;

  while (val != 2)
  {
    result = ReadEncoder();
    if (result == 0)
    {
      return 0;;
    } else
    {
      if (result == 1)
      {
        //val++;            // Clockwise          (CW)
        val = 2;
      }
      else
      {
        //val--;            // Counter-clockwise  (CCW)
        val = -2;
      }
      if (val == 2 || val == -2)
      { // It takes 2 pulses to make a rotation
        if (val > 0)
        { // CW??
          localDir = 1;
        } else
        { // Nope, CCW
          localDir = -1;
        }

        val = 1; // going too far to use the orignal code?
        return localDir;
      }
    }
  }
}
