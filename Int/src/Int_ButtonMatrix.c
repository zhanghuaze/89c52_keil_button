#include "Int_ButtonMatrix.h"


/**
 * @brief 检查按钮矩阵是否有按键被按下
 *
 * @return uint8_t 返回按下的按钮编号，如果没有按键被按下则返回0
 */
uint8_t Int_ButtonMatrix_IsPressed(void)
{
    uint8_t i, j;

    uint8_t lines[4] = {0xFE, 0xFD, 0xFB, 0xF7};   // 行扫描码，分别对应第一行到第四行
    uint8_t columns[4] = {0x10, 0x20, 0x40, 0x80}; // 列引脚

    for (i = 0; i < 4; i++)
    {
        P2 = lines[i]; // 设置当前行为低电平，其他行为高电平

        for (j = 0; j < 4; j++)
        {
            if ((P2 & columns[j]) == 0x00) // 检测当前列是否为低电平，表示按钮被按下
            {
                Com_Util_Delay(10); // 抖动延时

                if ((P2 & columns[j]) == 0x00) // 再次检测当前列是否为低电平，确认按钮仍然被按下
                {
                    while ((P2 & columns[j]) == 0x00); // 等待按钮释放
                    return (j + 1) + 10 * (i + 1); // 返回按钮编号，行号 * 10 + 列号
                }
            }
        }
    }

    return 0; // 没有按钮被按下
}
