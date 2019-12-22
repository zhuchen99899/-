#ifndef __wifi_H_
#define __wifi_H_
#include "sys.h"
#include "stdio.h"	


#define USART2_REC_LEN  			300  	//定义最大接收字节数 200
#define EN_USART2_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART2_RX_BUF[USART2_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STA;         		//接收状态标记	
void WIFI_init(u32 bound);



void USART2_IRQHandler(void);  

void Usart_SendString(USART_TypeDef* USARTx,char *str);
#endif



