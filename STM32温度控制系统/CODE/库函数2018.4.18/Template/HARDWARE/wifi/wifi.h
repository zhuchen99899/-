#ifndef __wifi_H_
#define __wifi_H_
#include "sys.h"
#include "stdio.h"	
void WIFI_init(u32 bound);



void USART2_IRQHandler(void);  

void Usart_SendString(USART_TypeDef* USARTx,char *str);
#endif



