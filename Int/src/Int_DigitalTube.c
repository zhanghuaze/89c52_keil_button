#include "Int_DigitalTube.h"


#define SEG_LATCH P14
#define DIG_LATCH P15

// 数码管数字显示
// 		dp	g	f	e	d	c	b	a	

// 0	0	0	1	1 	1	1	1	1	0x3F
// 1	0	0	0	0 	0	1	1	0	0x06
// 2	0	1	0	1 	1	0	1	1	0x5B
// 3	0	1	0	0	1	1	1	1	0x4F
// 4	0	1	1	0 	0	1	1	0	0x66
// 5	0	1	1	0 	1	1	0	1	0x6D
// 6	0	1	1	1 	1	1	0	1	0x7D
// 7	0	0	0	0 	0	1	1	1	0x07
// 8	0	1	1	1 	1	1	1	1	0x7F
// 9	0	1	1	0 	1	1	1	1	0x6F
static uint8_t g_DigitalTubeNum[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};


/**
 * @brief 显示单个数码管
 * 
 * @param position 选择的数码管位置，1-8
 * @param seg_code 段码
 */
void Int_DigitalTube_DisplaySingle(uint8_t position, uint8_t seg_code)
{
    // 段选
    P0 = seg_code;          //P0输出段码
    SEG_LATCH = 0;          //段锁存LE拉高
    Com_Util_Delay(1);      //延时，保证锁存
    SEG_LATCH = 1;          //下降沿锁存数据

    // 位选
    P0 = ~position;         //P0输出位选码
    DIG_LATCH = 0;          //位锁存LE拉高
    Com_Util_Delay(1);      //延时，保证锁存
    DIG_LATCH = 1;          //下降沿锁存

    P0 = 0x00;              //消隐：全部熄灭，防止拖影
    SEG_LATCH = 0;
    Com_Util_Delay(1);      //延时，保证锁存
    SEG_LATCH = 1;
    DIG_LATCH = 0;
    Com_Util_Delay(1);      //延时，保证锁存
    DIG_LATCH = 1;
}


void Int_DigitalTube_DisplayNumber(uint32_t number)
{
    uint8_t digit1 = number / 10000000; // 千万位
    uint8_t digit2 = number / 1000000; // 百万位
    uint8_t digit3 = number / 100000; // 十万位
    uint8_t digit4 = number / 10000; // 万位
    uint8_t digit5 = number / 1000; // 千位
    uint8_t digit6 = number / 100; // 百位
    uint8_t digit7 = number / 10; // 十位
    uint8_t digit8 = number % 10; // 个位

    Int_DigitalTube_DisplaySingle(1, g_DigitalTubeNum[digit1]);
    Int_DigitalTube_DisplaySingle(2, g_DigitalTubeNum[digit2]);
    Int_DigitalTube_DisplaySingle(3, g_DigitalTubeNum[digit3]);
    Int_DigitalTube_DisplaySingle(4, g_DigitalTubeNum[digit4]);
    Int_DigitalTube_DisplaySingle(5, g_DigitalTubeNum[digit5]);
    Int_DigitalTube_DisplaySingle(6, g_DigitalTubeNum[digit6]);
    Int_DigitalTube_DisplaySingle(7, g_DigitalTubeNum[digit7]);
    Int_DigitalTube_DisplaySingle(8, g_DigitalTubeNum[digit8]);
}