#ifndef __DRI_TIMER0_H__
#define __DRI_TIMER0_H__

typedef void (*Timer0_Callback)(void); // 定义定时器0回调函数类型

void Dri_Timer0_Init(void);
bit Dri_Timer0_RegisterCallback(Timer0_Callback callback);
bit Dri_Timer0_UnregisterCallback(Timer0_Callback callback);

#endif /* __DRI_TIMER0_H__ */