#include "Com_Util.h"
#include "Dri_Timer0.h"
#include <STC89C5xRC.H>

#define TIMER0_MAX_CALLBACKS 4                                // 定义最大回调函数数量
static Timer0_Callback timer0_callback[TIMER0_MAX_CALLBACKS]; // 定义定时器0回调函数数组

/**
 * @brief 初始化定时器0，周期为1ms
 *
 */
void Dri_Timer0_Init()
{
    uint8_t i = 0;

    // 1.启用中断
    EA = 1;  // 全局中断使能
    ET0 = 1; // 定时器0中断使能

    // 2. 工作模式: Gate=0, C/T=0, M1=0, M0=1 (16位定时器模式)
    TMOD &= 0xF0;
    TMOD |= 0x01;

    // 3. 设置脉冲计数器的初始值 1ms
    TL0 = 64614;
    TH0 = 64614 >> 8;

    // 4. 开启定时器
    TF0 = 0; // 清除定时器溢出标志
    TR0 = 1; // 启动定时器0

    for (i = 0; i < TIMER0_MAX_CALLBACKS; i++) // 初始化回调函数数组
    {
        timer0_callback[i] = NULL; // 将回调函数指针初始化为NULL
    }
}

/**
 * @brief 注册定时器0的回调函数
 *
 * @param callback 回调函数指针
 * @return bit 注册是否成功
 */
bit Dri_Timer0_RegisterCallback(Timer0_Callback callback)
{
    uint8_t i = 0;

    // 检查数组中是否已经注册过函数
    for (i = 0; i < TIMER0_MAX_CALLBACKS; i++)
    {
        if (timer0_callback[i] == callback)
        {
            return 1;
        }
    }

    for (i = 0; i < TIMER0_MAX_CALLBACKS; i++) // 遍历回调函数数组
    {
        if (timer0_callback[i] == NULL) // 如果回调函数为空，则注册回调函数
        {
            timer0_callback[i] = callback;
            return 1;
        }
    }
    return 0;
}

/**
 * @brief 注销定时器0的回调函数
 *
 * @param callback 回调函数指针
 * @return bit 注销是否成功
 */
bit Dri_Timer0_UnregisterCallback(Timer0_Callback callback)
{
    uint8_t i = 0;

    for (i = 0; i < TIMER0_MAX_CALLBACKS; i++)
    {
        if (timer0_callback[i] == callback)
        {
            timer0_callback[i] = NULL;
            return 1;
        }
    }
    return 0;
}

/**
 * @brief 定时器0的服务函数
 *
 */
void Dri_Timer0_Routine(void) interrupt 1
{
    uint8_t i = 0;

    TL0 = 64614; // 设置定时器初始值
    TH0 = 64614 >> 8;

    for (i = 0; i < TIMER0_MAX_CALLBACKS; i++) // 遍历回调函数数组
    {
        if (timer0_callback[i] != NULL) // 如果回调函数不为空，则调用回调函数
        {
            timer0_callback[i](); // 调用回调函数
        }
    }
}
