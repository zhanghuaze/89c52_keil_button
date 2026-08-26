#include "Dri_UART.h"
#include "Com_Util.h"
#include "Dri_Timer0.h"
#include <STC89C5xRC.H>

static bit s_is_sending = 0; // 0：未在发送 1：正在发送
static char s_buff[16] = {0};
static uint8_t s_idle_count = 0;  // 空闲时间计数
static uint8_t s_index = 0;       // 读取的数据在缓冲区中的索引位置
static uint8_t s_is_complete = 0; // 表示数据是否接收完成 0-未完成 1-已完成

/**
 * @brief 判断串口数据接收完成
 *
 */
void Dri_UART_Timer0CallBack()
{
    s_idle_count++; // 空闲计数值每1ms自增

    // 空闲计数值超过10ms，认为数据接收完成
    if (s_index > 0 && s_idle_count >= 10)
    {
        s_is_complete = 1;
    }
}

/**
 * @brief 串口接收一个字符串
 *
 * @param str 接收缓存区指针
 * @return bit 是否接收完成
 */
bit Dri_UART_ReceiveString(char *str)
{
    if (s_is_complete) // 表示数据已经接收完成，通过延时进行的判断，10ms未接收到新的数据
    {
        uint8_t i;
        for (i = 0; i < s_index; i++)
        {
            str[i] = s_buff[i];
        }

        str[s_index] = '\0'; // 将数据的末尾跟上一个结束符，方便后续进行比较操作
        s_index = 0; // 接收指针清零，下次从起始位置开始接收数据
        s_is_complete = 0; // 标志位清零，用于下次接收数据
        return 1;
    }

    return 0;
}

/**
 * @brief 串口初始化
 *
 */
void Dri_UART_Init()
{
    // 1. 设置串口工作方式为方式1，8位UART，波特率可变
    SM0 = 0;
    SM1 = 1;

    // 2. 设置波特率
    // 2.1 配置SMOD
    PCON &= 0x7F; // 波特率不加倍
    // 2.2 配置定时器1参数
    // 2.2.1 工作模式：8位自动重装载定时器
    TMOD &= 0x0F;
    TMOD |= 0x20;
    // 2.2.2 配置定时器1的脉冲计数器初始值
    TH1 = 0xFD;
    TL1 = 0xFD;
    // 2.2.3 启动定时器1
    TR1 = 1;

    // 3. 接收数据相关配置
    REN = 1;
    SM2 = 0;

    // 4. 开启串口中断
    EA = 1;
    ES = 1;
    TI = 0;
    RI = 0;

    // 5. 注册空闲检测函数
    Dri_Timer0_RegisterCallback(Dri_UART_Timer0CallBack);
}

/**
 * @brief 使用串口发送一个字符
 *
 * @param c 待发送的字符
 */
void Dri_UART_SendChar(char c)
{
    while (s_is_sending == 1); // 等待之前的字符发送完成，发送完成后会在发送中断中清零该标志位
    
    SBUF = c; // 将准备发送的字符写入到发送缓冲区寄存器中

    s_is_sending = 1; // 置位标志位，表示当前正在发送新的字符
}

/**
 * @brief 使用串口发送一个字符串
 *
 * @param str 待发送的字符串
 */
void Dri_UART_SendString(char *str)
{
    // 字符串以'\0'作为结束符，当不为零，表示仍未发送结束
    while (*str != '\0')
    {
        Dri_UART_SendChar(*str);
        str++;
    }
}

/**
 * @brief 串口中断服务程序
 *
 */
void Dri_UART_Handler(void) interrupt 4
{
    // 接收到数据
    if (RI)
    {
        s_buff[s_index++] = SBUF; // 将接收到的字符读取到接收数据缓冲区中

        s_idle_count = 0; // 空闲计数值重新计数，表示接收到新的数据了

        RI = 0;
    }

    // 发送完数据
    if (TI)
    {
        s_is_sending = 0; // 写入发送缓冲区寄存器的数据已经发送完成
        TI = 0;
    }
}