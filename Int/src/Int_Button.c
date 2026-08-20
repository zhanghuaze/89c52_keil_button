#include <STC89C5xRC.H>
#include "Int_Button.h"
#include "Com_Util.h"


/**
 * @brief Check if K41 button is pressed
 * 
 * @return bit Button is pressed (1) or not pressed (0)
 */
bit Int_Button_IsK41Pressed(void)
{
    if(K41 == 0)
    {
        Com_Util_Delay(10); // Delay for debouncing

        if(K41 == 0) // Check if the button is still pressed
        {
            while(K41 == 0); // Wait until the button is released
            return 1; // Button is pressed
        }
    }
    return 0; // Button is not pressed
}


/**
 * @brief Check if K42 button is pressed
 * 
 * @return bit Button is pressed (1) or not pressed (0)
 */
bit Int_Button_IsK42Pressed(void)
{
    if(K42 == 0)
    {
        Com_Util_Delay(10); // Delay for debouncing

        if(K42 == 0) // Check if the button is still pressed
        {
            while(K42 == 0); // Wait until the button is released
            return 1; // Button is pressed
        }
    }
    return 0; // Button is not pressed
}


/**
 * @brief Check if K43 button is pressed
 * 
 * @return bit Button is pressed (1) or not pressed (0)
 */
bit Int_Button_IsK43Pressed(void)
{
    if(K43 == 0)
    {
        Com_Util_Delay(10); // Delay for debouncing

        if(K43 == 0) // Check if the button is still pressed
        {
            while(K43 == 0); // Wait until the button is released
            return 1; // Button is pressed
        }
    }
    return 0; // Button is not pressed
}


/**
 * @brief Check if K44 button is pressed
 * 
 * @return bit Button is pressed (1) or not pressed (0)
 */
bit Int_Button_IsK44Pressed(void)
{
    if(K44 == 0)
    {
        Com_Util_Delay(10); // Delay for debouncing

        if(K44 == 0) // Check if the button is still pressed
        {
            while(K44 == 0); // Wait until the button is released
            return 1; // Button is pressed
        }
    }
    return 0; // Button is not pressed
}