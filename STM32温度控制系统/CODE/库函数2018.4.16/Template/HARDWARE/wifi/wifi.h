#ifndef __wifi_H_
#define __wifi_H_
#include "sys.h"
#include "stdio.h"	

void WIFI_init(u32 bound);


void USART_Putchar(USART_TypeDef* USARTx,uint8_t Data);
	



void UART_PutStr(USART_TypeDef* USARTx,uint8_t *str);




void USART2_IRQHandler(void);  

#endif



