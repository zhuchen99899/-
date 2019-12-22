#ifndef __TIMER_H_
#define __TIMER_H_
#include "sys.h"
void Timer2_Init(u16 arr,u16 psc);
void TIM2_IRQHandler(void);

#endif

