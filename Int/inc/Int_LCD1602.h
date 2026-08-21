#ifndef __INT_LCD1602_H__
#define __INT_LCD1602_H__

//用户调用函数：
void Int_LCD1602_Init();
void Int_LCD1602_ShowChar(unsigned char Line,unsigned char Column,char Char);
void Int_LCD1602_ShowString(unsigned char Line,unsigned char Column,char *String);
void Int_LCD1602_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void Int_LCD1602_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);
void Int_LCD1602_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void Int_LCD1602_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);

#endif
