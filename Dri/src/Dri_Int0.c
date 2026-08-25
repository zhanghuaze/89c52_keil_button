#include "Dri_Int0.h"
#include <STC89C5xRC.H>


/**
 * @brief 外部中断0的服务函数
 * 
 */
void Dri_Int0_Routine(void) interrupt 0
{
    // 外部中断0的处理逻辑
    if(IE0)
    {
        P0 = ~P0; // 反转P0口的状态
    }
}


/**
 * @brief 初始化外部中断0
 * 
 */
void Dri_Int0_Init(void)
{
    // 配置外部中断0的触发方式和使能中断
    IT0 = 1; // 设置为下降沿触发
    EX0 = 1; // 使能外部中断0
    EA = 1;  // 全局中断使能
}