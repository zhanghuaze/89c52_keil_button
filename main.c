#include "Com_Util.h"
#include "Dri_UART.h"
#include <STC89C5xRC.H>
#include <STRING.H>
#include "Dri_Timer0.h"


char g_ReceiveBuff[20]; // 串口接收数据缓冲区


/**
 * @brief 主函数
 *
 */
void main(void)
{
    Dri_Timer0_Init(); // 定时器0初始化
    Dri_UART_Init(); // 串口初始化，需在定时器初始化之后进行

    while (1)
    {
        // 循环查询串口是否接收到数据
        if (Dri_UART_ReceiveString(g_ReceiveBuff)) // 将接收到的数据保存到数据缓冲区
        {
            Dri_UART_SendString(g_ReceiveBuff);

            // 注意：两个字符串自左向右逐个字符相比（按ASCII值大小相比较），直到出现不同的字符或遇'\0'为止
            if (strcmp("on", g_ReceiveBuff) == 0)
            {
                P0 = 0x00;
                Dri_UART_SendString("LED is on!");
            }
            else if (strcmp("off", g_ReceiveBuff) == 0)
            {
                P0 = 0xFF;
                Dri_UART_SendString("LED is off!");
            }
            else
            {
                Dri_UART_SendString("err!");
            }
        }
    }
}
