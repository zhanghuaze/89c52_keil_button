#include "Com_Util.h"
#include "Int_ButtonMatrix.h"
#include "Int_LCD1602.h"
#include <STC89C5xRC.H>


/**
 * @brief 主函数
 *
 */
void main(void)
{
    uint8_t buttonNumber; // 按钮编号

    Int_LCD1602_Init(); // 初始化LCD1602显示屏

    while (1)
    {
        Int_LCD1602_ShowString(1, 1, "Button: "); // 显示按钮提示信息

        buttonNumber = Int_ButtonMatrix_IsPressed(); // 检查按钮矩阵是否有按键被按下

        if (buttonNumber) // 如果有按键被按下
        {
            Int_LCD1602_ShowNum(2, 1, buttonNumber, 2); // 显示按下的按钮编号
        }
    }
}
