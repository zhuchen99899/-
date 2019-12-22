#include "sys.h"
#include "key.h"
#include "EXTI.h"
#include "delay.h"

extern float Keytem;

void EXTIX(void)
{
	NVIC_InitTypeDef NVIC_InitStrue;
	EXTI_InitTypeDef EXIT_InitStrue;
key_init();  //外部中断GPIO口设置
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //使能端口复用（复用位外部中断口）时钟
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);//PE2映射到外部中断线2上
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);//PE3映射到外部中断线3上
	
	EXIT_InitStrue.EXTI_Line=EXTI_Line2;      //外部中断线2
	EXIT_InitStrue.EXTI_LineCmd=ENABLE;	             //中断线使能
	EXIT_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;	//中断模式：中断（中断、事件）
	EXIT_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling;//中断触发方式：下降沿
	//外部中断初始化结构体成员变量赋值
	EXTI_Init(&EXIT_InitStrue);
	
		EXIT_InitStrue.EXTI_Line=EXTI_Line3;      //外部中断线3
	EXIT_InitStrue.EXTI_LineCmd=ENABLE;	             //中断线使能
	EXIT_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;	//中断模式：中断（中断、事件）
	EXIT_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling;//中断触发方式：下降沿
	//外部中断初始化结构体成员变量赋值
	EXTI_Init(&EXIT_InitStrue);
	
NVIC_InitStrue.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;
	
	NVIC_Init(&NVIC_InitStrue);
	//NVIC中断初始化

	
NVIC_InitStrue.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;
	
	NVIC_Init(&NVIC_InitStrue);
	//NVIC中断初始化
}


/*
void EXTI3(void)
{
	NVIC_InitTypeDef NVIC_InitStrue;
	EXTI_InitTypeDef EXIT_InitStrue;
key_init();  //外部中断GPIO口设置
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //使能端口复用（复用位外部中断口）时钟
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);//PE3映射到外部中断线3上
	
	
	EXIT_InitStrue.EXTI_Line=EXTI_Line3;      //外部中断线3
	EXIT_InitStrue.EXTI_LineCmd=ENABLE;	             //中断线使能
	EXIT_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;	//中断模式：中断（中断、事件）
	EXIT_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling;//中断触发方式：下降沿
	//外部中断初始化结构体成员变量赋值
	EXTI_Init(&EXIT_InitStrue);
	
NVIC_InitStrue.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;
	
	NVIC_Init(&NVIC_InitStrue);
	//NVIC中断初始化

}

*/

/*
void EXTI2_IRQHandler(void)
{




	if(KEY2==0) 
	{
	delay_ms(10);
	Keytem+=1;

	}


EXTI_ClearITPendingBit(EXTI_Line2); //清除中断标志位置。以下一次进入中断服务函数。（中断发生后标志位置1）

}


void EXTI3_IRQHandler(void)
{
	



	if(KEY1==0) 
	{
	delay_ms(10);
	Keytem-=1;

	}

EXTI_ClearITPendingBit(EXTI_Line3); //清除中断标志位置。以下一次进入中断服务函数。（中断发生后标志位置1）


}

*/

