#ifndef __DRI_UART_H__
#define __DRI_UART_H__

void Dri_UART_Init();
void Dri_UART_SendChar(char c);
void Dri_UART_SendString(char *str);
//bit Dri_UART_ReceiveChar(char *c);
void Dri_UART_Timer0CallBack();
bit Dri_UART_ReceiveString(char *str);

#endif /* __DRI_UART_H__ */