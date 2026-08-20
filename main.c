#include <STC89C5xRC.H>
#include "Com_Util.h"
#include "Int_Button.h"

sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;
sbit LED4 = P0^3;

void main(void)
{
    while (1)
    {
        if (Int_Button_IsK41Pressed())
        {
            // Handle K41 button press
            LED1 = !LED1; // Toggle LED1
        }

        if (Int_Button_IsK42Pressed())
        {
            // Handle K42 button press
            LED2 = !LED2; // Toggle LED2
        }

        if (Int_Button_IsK43Pressed())
        {
            // Handle K43 button press
            LED3 = !LED3; // Toggle LED3
        }

        if (Int_Button_IsK44Pressed())
        {
            // Handle K44 button press
            LED4 = !LED4; // Toggle LED4
        }
    }
}
