#include "Com_Util.h"
#include "Dri_Timer0.h"
#include <STC89C5xRC.H>

void LED_Blink(void)
{
    static uint16_t count;

    count++;

    if (count >= 1000)
    {
        P20 = ~P20;
        count = 0;
    }
}

/**
 * @brief 主函数
 *
 */
void main(void)
{
    Dri_Timer0_Init();
    Dri_Timer0_RegisterCallback(LED_Blink);
    
    while (1)
    {
    }
}
