
#ifndef Utilities_H_
#define Utilities_H_

#include "nvs_flash.h"
#include "nvs.h"

typedef enum {WORDSPERMINUTE = 0, SIDETONE,  WHICHISDITPADDLE, FARSWORTHSPEED,  KOCHSPEED, ENCODINGACTIVE, VOLUME} nvParm;

/*
 * These are the parameters the legacy code saves--as far as I can tell . We add volume
 * 
  // ****** todo status = EEPROM.write((uint16_t) WORDSPERMINUTE,   wordsPerMinute);
  // ****** todo status = EEPROM.write((uint16_t) SIDETONE,         sidetoneFrequency);
  // ****** todo status = EEPROM.write((uint16_t) WHICHISDITPADDLE, ditPaddle);
  // ****** todo status = EEPROM.write((uint16_t) FARSWORTHSPEED,   farnsworthWPM);
  // ****** todo status = EEPROM.write((uint16_t) KOCHSPEED,        kochSpeed);
  // *****  todo// status = EEPROM.write((uint16_t) ENCODINGACTIVE, encodingType);

  //statusFlag = WriteEEPROMValue(WORDSPERMINUTE, wordsPerMinute);
  //statusFlag = WriteEEPROMValue(KOCHSPEED,      targetWPM);
  //statusFlag = WriteEEPROMValue(FARSWORTHSPEED, farnsworthWPM);
  //statusFlag = WriteEEPROMValue(ENCODINGACTIVE, encodingType);//which encoding is active?

  OK, so 
  wordsPerMinute is current keyer speed -- SetKeyerSpeed()
  targetWPM is also called KOCHSPEED in WPM (see below)
  encodingType is FARSWORTHSPEED or standard -- SetEncodingType()
              after SetEncodingType() we call (from the top level switch):
                   targetWPM     = SetTargetWPM();//also KOCHSPEED
                   farnsworthWPM = SetFarnsworthWPM();
                   
  FARSWORTHSPEED is farnsworthWPM--SetFarnsworthWPM() 
  
As far as I can tell
So what is "Standard" encoding?
I think "Standard" is not farnsworth.
Yes, because SetTargetWPM() and SetFarnsworthWPM() are only called when 
if (encodingType == FARNSWORTHENCODING) in the top level switch statement.

So how and what do we save in NVS--

wordsPerMinute is current keyer speed -- SetKeyerSpeed()
setParameterState() is called in SetKeyerSpeed()
// local name
//uint16_t lastWordsPerMinute;
// global name
//extern  uint16_t  wordsPerMinute;
//uint16_t  wordsPerMinute;
// nvs key name: "wordsPerMinute"
// nvParm: WORDSPERMINUTE

SetNewSidetone() frequency
setParameterState() is called in SetNewSidetone()
//uint16_t lastSidetoneFrequency;
//extern   uint16_t sidetoneFrequency;
// nvs key name: "sidetoneFreq"
// nvParm: SIDETONE

We don't use this anymore--just change the #define or swap the wires
//uint16_t lastDitPaddle;
//extern   uint16_t ditPaddle;
// nvs key name: "ditPaddle"
// nvParm: WHICHISDITPADDLE

//setVol() sets float volume
//float lastVolume;
//extern float  Volume;
// nvs key name: "Volume"
// nvParm: VOLUME
//setParameterState() is called in setVol()


//uint16_t lastFarnsworthWPM;
//extern  uint16_t farnsworthWPM;
// nvs key name: "farnsWPM"
// nvParm: FARSWORTHSPEED
setParameterState() is called in SetFarnsworthWPM()

//uint16_t lastEncodingType;
//extern uint16_t  encodingType;
// nvs key name: "encodeType"
// nvParm: ENCODINGACTIVE
setParameterState() is called in SetEncodingType()

//uint16_t lastKochSpeed;
//extern uint16_t  kochSpeed;
// nvs key name: "kochSpeed"
// nvParm: KOCHSPEED
We have deduced that this is
SetTargetWPM() and setParameterState() is called in SetTargetWPM()
//statusFlag = WriteEEPROMValue(KOCHSPEED,      targetWPM);
The Farnsworth method for learning sends letters at the speed you hope to ultimately reach (e.g., targetWPM),
but instead of a letter space at the target speed, the Farnsworth method has the character spacing at a much
lower speed. For example, you might hope to get to 35wpm, but set the Farnsworth (spacing) speed at 5wpm. The
advantage is that you listen for rhythms rather than dits and dahs.
 
*/ 
// TODO: replace setParameterState() with nvParm data type arg
// to call with this struct as arg

typedef struct 
{
  uint16_t* localVal;
  uint16_t* globalVal;
  float*    floatVal;
  nvParm    key; 
  char      name[16]; 
} NVSinfo;


/*
Return
ESP_OK if value was set successfully
ESP_ERR_NVS_INVALID_HANDLE if handle has been closed or is NULL
ESP_ERR_NVS_READ_ONLY if storage handle was opened as read only
ESP_ERR_NVS_INVALID_NAME if key name doesn’t satisfy constraints
ESP_ERR_NVS_NOT_ENOUGH_SPACE if there is not enough space in the underlying storage to save the value
ESP_ERR_NVS_REMOVE_FAILED if the value wasn’t updated because flash write operation has failed. 
                          The value was written however, and update will be finished after 
                          re-initialization of nvs, provided that flash operation doesn’t fail again.
ESP_ERR_NVS_VALUE_TOO_LONG if the string value is too long

Parameters
handle: Handle obtained from nvs_open function. Handles that were opened read only cannot be used.

key: Key name. Maximal length is determined by the underlying implementation, 
     but is guaranteed to be at least 15 characters. Shouldn’t be empty.
     
value: The value to set. For strings, the maximum length (including null character) is 4000 bytes.

esp_err_t nvs_set_i32(nvs_handle_thandle, const char *key, int32_t value)
esp_err_t nvs_set_u32(nvs_handle_thandle, const char *key, uint32_t value)
___________________________________________________________________________
Return
ESP_OK if storage handle was opened successfully
ESP_ERR_NVS_NOT_INITIALIZED if the storage driver is not initialized
ESP_ERR_NVS_PART_NOT_FOUND if the partition with label “nvs” is not found
ESP_ERR_NVS_NOT_FOUND id namespace doesn’t exist yet and mode is NVS_READONLY
ESP_ERR_NVS_INVALID_NAME if namespace name doesn’t satisfy constraints
other error codes from the underlying storage driver
Parameters
name: Namespace name. Maximal length is determined by the underlying implementation, 
      but is guaranteed to be at least 15 characters. Shouldn’t be empty.
open_mode: NVS_READWRITE or NVS_READONLY. If NVS_READONLY, will open a handle for reading only. 
           All write requests will be rejected for this handle.
out_handle: If successful (return code is zero), handle will be returned in this argument.

esp_err_t nvs_open(const char *name, nvs_open_mode_topen_mode, nvs_handle_t *out_handle)
_______________________________________________________________________________
Close the storage handle and free any allocated resources.

This function should be called for each handle opened with nvs_open once the handle is not in use any more. 
Closing the handle may not automatically write the changes to nonvolatile storage. 
This has to be done explicitly using nvs_commit function. Once this function is called on a handle, 
the handle should no longer be used.

Parameters
handle: Storage handle to close

void nvs_close(nvs_handle_thandle)
_______________________________________________________________________________
Return
ESP_OK if the value was retrieved successfully
ESP_ERR_NVS_NOT_FOUND if the requested key doesn’t exist
ESP_ERR_NVS_INVALID_HANDLE if handle has been closed or is NULL
ESP_ERR_NVS_INVALID_NAME if key name doesn’t satisfy constraints
ESP_ERR_NVS_INVALID_LENGTH if length is not sufficient to store data

NOTE:
NVS operates on key-value pairs. Keys are ASCII strings; the maximum key length is 
currently 15 characters. Values can have one of the following types:

integer types: uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, uint64_t, int64_t
zero-terminated string
variable length binary data (blob)
Parameters
handle: Handle obtained from nvs_open function.
key: Key name. Maximal length is determined by the underlying implementation, 
     but is guaranteed to be at least 15 characters. Shouldn’t be empty.
out_value: Pointer to the output value. May be NULL for nvs_get_str and nvs_get_blob, 
           in this case required length will be returned in length argument.
length: A non-zero pointer to the variable holding the length of out_value. 
        In case out_value a zero, will be set to the length required to hold the value. 
        In case out_value is not zero, will be set to the actual length of the value written. 
        For nvs_get_str this includes zero terminator.

esp_err_t nvs_get_i32(nvs_handle_thandle, const char *key, int32_t *out_value)


*/

//void syncParameterState(void);
void nonVolatileStorageInit(void);
void setParameterState(nvParm Parm);

#endif /* Utilities_H_ */
