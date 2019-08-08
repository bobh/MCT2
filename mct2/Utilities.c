/*

    https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/storage/nvs_flash.html

*/


#include "Utilities.h"
extern esp_err_t err;
extern nvs_handle my_handle;
extern  uint16_t  wordsPerMinute;
extern  uint16_t sidetoneFrequency;
extern  uint16_t ditPaddle;
extern  uint16_t farnsworthWPM;
extern uint16_t  kochSpeed;
extern uint16_t  encodingType;
extern float     volume;

uint16_t lastWordsPerMinute;
uint16_t lastSidetoneFrequency;
uint16_t lastDitPaddle;
uint16_t lastFarnsworthWPM;
uint16_t lastKochSpeed;
uint16_t lastEncodingType;
uint16_t lastVolume;
/*

  Example printfs of Initialize/Restore sequence for sidetone freq, WPM already stored
  Reading from NVS ...
  Opening Non-Volatile Storage (NVS) handle... Done
  Reading parameters from NVS ... Done
  lastWordsPerMinute = 15
  The value is not initialized yet!
  Error (ESP_OK) reading!
  Done
  // restore sequence for sidetone freq
  Reading from NVS ...
  Opening Non-Volatile Storage (NVS) handle... Done
  Reading parameters from NVS ... Done
  lastWordsPerMinute = 15
  Done
  lastSidetoneFrequency = 700
*/


/*
  // Initalize non volatile storage (nvs)
  // If it has never been written to, write/save some defaults
  // else store the current
  // Do this for all savable parameters
*/
void nonVolatileStorageInit(void)
{

  // Initialize NVS
  err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES)
  {
    // NVS partition was truncated and needs to be erased
    // Retry nvs_flash_init
    ESP_ERROR_CHECK(nvs_flash_erase());
    err = nvs_flash_init();
    printf("No Free Pages\n");
    return;

  }
  ESP_ERROR_CHECK( err );

  printf("Reading from NVS ... ");
  // Open
  printf("\n");
  printf("Opening Non-Volatile Storage (NVS) handle... ");
  err = nvs_open("storage", NVS_READWRITE, &my_handle);
  if (err != ESP_OK)
  {
    printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    return;
  } else
  {
    printf("Done\n");
    printf("Reading parameters from NVS ... ");

    // ||||||||||||||||||||| wordsPerMinute |||||||||||||||||||||||||||||||
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    // Read
    err = nvs_get_i32(my_handle, "wordsPerMinute", &lastWordsPerMinute);
    switch (err)
    {
      case ESP_OK: // saved parameter was found in nvs
        printf("Done\n");
        printf("lastWordsPerMinute = %d\n", lastWordsPerMinute);
        // this is Init, store NVS value to global value
        // but qualify parameter first
        if ( (lastWordsPerMinute >= 5) && (lastWordsPerMinute <= 50) )
        {
          wordsPerMinute = lastWordsPerMinute;
        }
        else
        {
          wordsPerMinute = 15;
        }

        break;
      case ESP_ERR_NVS_NOT_FOUND: //parameter hasn't been initialized yet
        printf("The value is not initialized yet!\n");
        // set default
        lastWordsPerMinute = 15;
        wordsPerMinute = 15;
        // write an initial value to non-volatile memory
        err = nvs_set_i32(my_handle, "wordsPerMinute", lastWordsPerMinute);
        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
        printf("Error (%s) initial write!\n", esp_err_to_name(err));
        break;
      default :
        printf("Error (%s) reading!\n", esp_err_to_name(err));
    }

    // ||||||||||||||||||||| sidetoneFreq ||||||||||||||||||||||||||||||||
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    // re-use handle
    err = nvs_get_i32(my_handle, "sidetoneFreq", &lastSidetoneFrequency);
    switch (err)
    {
      case ESP_OK: // saved parameter was found in nvs
        printf("Done\n");
        printf("lastSidetoneFrequency = %d\n", lastSidetoneFrequency);
        // this is Init, store NVS value to global value
        // but qualify parameter first
        if ( (lastSidetoneFrequency > 50) && (lastSidetoneFrequency <= 2000) )
        {
          sidetoneFrequency = lastSidetoneFrequency;
        }
        else
        {
          sidetoneFrequency = 700;
        }
        break;
      case ESP_ERR_NVS_NOT_FOUND: //parameter hasn't been initialized yet
        printf("The value is not initialized yet!\n");
        // set default
        lastSidetoneFrequency = 700;
        sidetoneFrequency = 700;
        // write an initial value to non-volatile memory
        // stores a single precision float blob in an i32
        err = nvs_set_i32(my_handle, "sidetoneFreq", lastSidetoneFrequency);
        printf("Error (%s) reading!\n", esp_err_to_name(err));

        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
        break;
      default :
        printf("Error (%s) reading!\n", esp_err_to_name(err));
    }

    // ||||||||||||||||||||| farnsworthWPM ||||||||||||||||||||||||||||||||
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    // re-use the handle
    err = nvs_get_i32(my_handle, "farnsWPM", &lastFarnsworthWPM);
    switch (err)
    {
      case ESP_OK: // saved parameter was found in nvs
        printf("Done\n");
        printf("lastFarnsworthWPM = %d\n", lastFarnsworthWPM);
        // this is Init, store NVS value to global value
        // but qualify parameter first
        if ( (lastWordsPerMinute >= 5) && (lastWordsPerMinute <= 50) )
        {
          farnsworthWPM = lastFarnsworthWPM;
        }
        else
        {
          farnsworthWPM = 15;
        }

        break;
      case ESP_ERR_NVS_NOT_FOUND: //parameter hasn't been initialized yet
        printf("The value is not initialized yet!\n");
        // set default
        // without really knowing what we're doing, let's set default to 15
        lastFarnsworthWPM = 15;
        farnsworthWPM = 15;
        // write an initial value to non-volatile memory
        err = nvs_set_i32(my_handle, "farnsWPM", lastFarnsworthWPM);
        printf("Error (%s) reading!\n", esp_err_to_name(err));

        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
        break;
      default :
        printf("Error (%s) reading!\n", esp_err_to_name(err));
    }
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



    // ||||||||||||||||||||| lastKochSpeed ||||||||||||||||||||||||||||||||
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    // re-use the handle
    err = nvs_get_i32(my_handle, "kochSpeed", &lastKochSpeed);
    switch (err)
    {
      case ESP_OK: // saved parameter was found in nvs
        printf("Done\n");
        printf("lastKochSpeed = %d\n", lastKochSpeed);
        // this is Init, store NVS value to global value
        // but qualify parameter first
        if ( (lastKochSpeed >= 5) && (lastKochSpeed <= 50) )
        {
          kochSpeed = lastKochSpeed;
        }
        else
        {
          kochSpeed = 15;
        }

        break;
      case ESP_ERR_NVS_NOT_FOUND: //parameter hasn't been initialized yet
        printf("The value is not initialized yet!\n");
        // set default
        // without really knowing what we're doing, let's set default to 15
        lastKochSpeed = 15;
        kochSpeed = 15;
        // write an initial value to non-volatile memory
        err = nvs_set_i32(my_handle, "kochSpeed", lastKochSpeed);
        printf("Error (%s) reading!\n", esp_err_to_name(err));

        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
        break;
      default :
        printf("Error (%s) reading!\n", esp_err_to_name(err));
    }
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



    // ||||||||||||||||||||| lastEncodingType |||||||||||||||||||||||||||||
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    // re-use the handle
    err = nvs_get_i32(my_handle, "encodeType", &lastEncodingType);
    switch (err)
    {
      case ESP_OK: // saved parameter was found in nvs
        printf("Done\n");
        printf("lastEncodingType = %d\n", lastEncodingType);
        // this is Init, store NVS value to global value
        // but qualify parameter first
        // NORMALENCODING         0                  // Standard encoding
        // FARNSWORTHENCODING     1                  // Requires target and Farnsworth speeds
        if ( (lastEncodingType == 0) || (lastEncodingType == 1) )
        {
          encodingType = lastEncodingType;
        }
        else
        {
          encodingType = 0; // normal
        }

        break;
      case ESP_ERR_NVS_NOT_FOUND: //parameter hasn't been initialized yet
        printf("The value is not initialized yet!\n");
        // set default
        // without really knowing what we're doing, let's set default to normal
        lastEncodingType = 0;
        encodingType = 0;
        // write an initial value to non-volatile memory
        err = nvs_set_i32(my_handle, "encodeType", lastEncodingType);
        printf("Error (%s) reading!\n", esp_err_to_name(err));

        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
        break;
      default :
        printf("Error (%s) reading!\n", esp_err_to_name(err));
    }
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    // |||||||||||||||||||||||    lastVolume  |||||||||||||||||||||||||||||
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    // re-use the handle
    err = nvs_get_i32(my_handle, "Volume", &lastVolume);
    switch (err)
    {
      case ESP_OK: // saved parameter was found in nvs
        printf("Done\n");
        printf("lastVolume = %d\n", lastVolume);
        // this is Init, store NVS value to global value
        // but qualify parameter first
        if ( (lastVolume > 0) && (lastVolume <= 10) )
        {
          volume = lastVolume * 0.1;
        }
        else
        {
          volume = 0.5;
        }

        break;
      case ESP_ERR_NVS_NOT_FOUND: //parameter hasn't been initialized yet
        printf("The value is not initialized yet!\n");
        // set default
        volume = 0.5;
        lastVolume = volume * 10.0;
        // write an initial value to non-volatile memory
        err = nvs_set_i32(my_handle, "Volume", lastVolume);// OK to store a float? I don't think so!
        printf("Error (%s) reading!\n", esp_err_to_name(err));

        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
        break;
      default :
        printf("Error (%s) reading!\n", esp_err_to_name(err));
    }
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

  }

  printf("De-Alloc NVS Handle\n");
  // Close/De-alloc
  if (my_handle != NULL)
    nvs_close(my_handle);
}

// store a specific parameter in NVS
// the caller passes the parameter to be updated
// the parameter to be stored should already
// be in the global variable for the Parm specified by the caller
void setParameterState(nvParm Parm)
{
  // Open again
  printf("\n");
  printf("Opening Non-Volatile Storage (NVS) handle... ");
  err = nvs_open("storage", NVS_READWRITE, &my_handle);
  if (err != ESP_OK)
  {
    printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    return;

  } else
  { // open OK, update the paramater
    printf("Done\n");

    // Read it first
    printf("parameter from NVS ... ");

    switch (Parm)
    {
      // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
      case WORDSPERMINUTE:
        // read the current NVS value for the parameter of interest
        err = nvs_get_i32(my_handle, "wordsPerMinute", &lastWordsPerMinute);
        switch (err)
        {
          case ESP_OK:
            printf("Done\n");
            printf("lastWordsPerMinute = %d\n", lastWordsPerMinute);

            // Write
            printf("updating wordsPerMinute ... if required ");

            // qualify parameter--wordsPerMinute
            // lastWordsPerMinute is now the value read from NVS
            if ( (lastWordsPerMinute != wordsPerMinute) && (wordsPerMinute >= 5 ) && (wordsPerMinute <= 50) )
            {
              lastWordsPerMinute = wordsPerMinute; // from global (which should be current) to local

              err = nvs_set_i32(my_handle, "wordsPerMinute", lastWordsPerMinute);
              printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

              // Commit written value.
              // After setting any values, nvs_commit() must be called to ensure changes are written
              // to flash storage. Implementations may write to storage at other times,
              // but this is not guaranteed.
              printf("Committing updates in NVS ... ");
              err = nvs_commit(my_handle);
              printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
            }
            else
            {
              printf("No update in NVS needed and/or request for current ");
            }

            break;

          case ESP_ERR_NVS_NOT_FOUND:
            printf("The value is not initialized yet!\n");
            break;
          default :
            printf("Error (%s) reading!\n", esp_err_to_name(err));
        } // end switch err WORDSPERMINUTE

        break;
      // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
      case SIDETONE:
        // read the current NVS value for the parameter of interest
        err = nvs_get_i32(my_handle, "sidetoneFreq", &lastSidetoneFrequency);
        switch (err)
        {
          case ESP_OK:
            printf("Done\n");
            printf("lastSidetoneFrequency = %d\n", lastSidetoneFrequency);

            // Write
            printf("updating sidetoneFreq ... if required ");

            // qualify parameter--sidetoneFreq
            // lastSidetoneFrequency is now the value read from NVS
            if ( (lastSidetoneFrequency != sidetoneFrequency) && (sidetoneFrequency >= 100 ) && (sidetoneFrequency <= 2000) )
            {
              lastSidetoneFrequency = sidetoneFrequency; // from global (which should be current) to local

              err = nvs_set_i32(my_handle, "sidetoneFreq", lastSidetoneFrequency);
              printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

              // Commit written value.
              // After setting any values, nvs_commit() must be called to ensure changes are written
              // to flash storage. Implementations may write to storage at other times,
              // but this is not guaranteed.
              printf("Committing updates in NVS ... ");
              err = nvs_commit(my_handle);
              printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
            }
            else
            {
              printf("No update in NVS needed and/or request for current ");
            }
        }
        break;

      case WHICHISDITPADDLE: // this wasn't working in the original code--just switch the wires

        break;

      case FARSWORTHSPEED:
        // read the current NVS value for the parameter of interest
        err = nvs_get_i32(my_handle, "farnsWPM", &lastFarnsworthWPM);
        switch (err)
        {
          case ESP_OK:
            printf("Done\n");
            printf("farnsworthWPM = %d\n", lastFarnsworthWPM);

            // Write
            printf("updating farnsworthWPM ... if required ");

            // qualify parameter--sidetoneFreq
            // lastSidetoneFrequency is now the value read from NVS
            if ( (lastFarnsworthWPM != farnsworthWPM) && (farnsworthWPM >= 5 ) && (farnsworthWPM <= 50) )
            {
              lastFarnsworthWPM = farnsworthWPM; // from global (which should be current) to local

              err = nvs_set_i32(my_handle, "farnsWPM", lastFarnsworthWPM);
              printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

              // Commit written value.
              // After setting any values, nvs_commit() must be called to ensure changes are written
              // to flash storage. Implementations may write to storage at other times,
              // but this is not guaranteed.
              printf("Committing updates in NVS ... ");
              err = nvs_commit(my_handle);
              printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
            }
            else
            {
              printf("No update in NVS needed and/or request for current ");
            }
        }
        break;

      case KOCHSPEED:
        // read the current NVS value for the parameter of interest
        err = nvs_get_i32(my_handle, "kochSpeed", &lastKochSpeed);
        switch (err)
        {
          case ESP_OK:
            printf("Done\n");
            printf("kochSpeed = %d\n", lastKochSpeed);

            // Write
            printf("updating kochSpeed ... if required ");

            // qualify parameter--sidetoneFreq
            // lastSidetoneFrequency is now the value read from NVS
            if ( (lastKochSpeed != kochSpeed) && (kochSpeed >= 5 ) && (kochSpeed <= 50) )
            {
              lastKochSpeed = kochSpeed; // from global (which should be current) to local

              err = nvs_set_i32(my_handle, "kochSpeed", lastKochSpeed);
              printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

              // Commit written value.
              // After setting any values, nvs_commit() must be called to ensure changes are written
              // to flash storage. Implementations may write to storage at other times,
              // but this is not guaranteed.
              printf("Committing updates in NVS ... ");
              err = nvs_commit(my_handle);
              printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
            }
            else
            {
              printf("No update in NVS needed and/or request for current ");
            }
        }

        break;

      case ENCODINGACTIVE:

        // read the current NVS value for the parameter of interest
        err = nvs_get_i32(my_handle, "encodeType", &lastEncodingType);
        switch (err)
        {
          case ESP_OK:
            printf("Done\n");
            printf("kochSpeed = %d\n", lastEncodingType);

            // Write
            printf("updating EncodingType ... if required ");

            // qualify parameter--sidetoneFreq
            // lastSidetoneFrequency is now the value read from NVS
            if ( (lastEncodingType != encodingType) && (encodingType >= 0 ) && (encodingType <= 1) )
            {
              lastEncodingType = encodingType; // from global (which should be current) to local

              err = nvs_set_i32(my_handle, "encodeType", lastEncodingType);
              printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

              // Commit written value.
              // After setting any values, nvs_commit() must be called to ensure changes are written
              // to flash storage. Implementations may write to storage at other times,
              // but this is not guaranteed.
              printf("Committing updates in NVS ... ");
              err = nvs_commit(my_handle);
              printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
            }
            else
            {
              printf("No update in NVS needed and/or request for current ");
            }
        }

        break;

      case VOLUME:

        // read the current NVS value for the parameter of interest
        err = nvs_get_i32(my_handle, "Volume", &lastVolume);
        switch (err)
        {
          case ESP_OK:
            printf("Done\n");
            printf("Volume = %d\n", lastVolume);

            // Write
            printf("updating Volume ... if required ");

            // qualify parameter--volume
            // lastVolume is now the value read from NVS
            if ( (lastVolume > 0) && (lastVolume <= 10 ) || (lastVolume == 0) )
            {


              //if (lastVolume == 0) // this is to get around a development error
              //{                    // accidentally (code bug) initialized to 0
              //  printf("Corrupt initial value\n");
              //  printf("lastVolume = %d\n", lastVolume);
              //  lastVolume = 0.5*10.0;
              //}
              //else
              //{
              lastVolume = volume * 10.0; // from global (which should be current) to local
              // global is a float .1 -- 1.0
              //}

              err = nvs_set_i32(my_handle, "Volume", lastVolume);
              printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

              // Commit written value.
              // After setting any values, nvs_commit() must be called to ensure changes are written
              // to flash storage. Implementations may write to storage at other times,
              // but this is not guaranteed.
              printf("Committing updates in NVS ... ");
              err = nvs_commit(my_handle);
              printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
            }

            else
            {
              printf("No update in NVS needed and/or request for current ");
            }
        }



        break;

      default :

        printf("Error (%s) reading!\n", esp_err_to_name(err));

    }
  }

  printf("De-Alloc NVS Handle\n");
  // Close/De-alloc
  if (my_handle != NULL)
    nvs_close(my_handle);

}
