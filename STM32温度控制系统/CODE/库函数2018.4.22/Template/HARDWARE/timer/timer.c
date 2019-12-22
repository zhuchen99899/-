#include "sys.h"
#include "timer.h"

u32 CA=0;
u32 CB=0;
u32 CC=0;
extern u8 flag;
extern u8 flag_usart2;
extern u8 flag_KEY;
void Timer2_Init(u16 arr,u16 psc)
{
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue;
NVIC_InitTypeDef NVIC_Initstrue;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //通用定时器2RCC时钟使能
	
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;          //在预分频前的延时（不影响预分频系数），不常用
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;   //向上计数
	TIM_TimeBaseInitStrue.TIM_Period=arr;         //自动装载值
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc;            //时钟预分频系数

TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStrue);//定时器2寄存器初始化

TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//定时器2中断设置：更新中断（有某个寄存器更新，溢出中断）

	
	NVIC_Initstrue.NVIC_IRQChannel= TIM2_IRQn;  //TIM2中断通道
	NVIC_Initstrue.NVIC_IRQChannelCmd=ENABLE;	//IRQ中断通道使能
	NVIC_Initstrue.NVIC_IRQChannelPreemptionPriority=0; //抢占优先级为0
	NVIC_Initstrue.NVIC_IRQChannelSubPriority=3;	//子优先级为3
	NVIC_Init(&NVIC_Initstrue); //初始化NVIC中断优先级寄存器
	
	TIM_Cmd(TIM2,ENABLE); //使能定时器2
	
	
}

void TIM2_IRQHandler(void)
{

if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)       //计数器中断标志位 SET=1宏定义
	{
		CA++;
		CB++;
		CC++;
		if(CA>=20) 
		{
		flag=1;
		CA=0;
		}				
		
		if(CB>=1000)   //WIFI发送 定时
		{
		flag_usart2=1;
			CB=0;
		}
	/*	if(CC>=5)
		{
		
		flag_KEY=1;
			CC=0;
		}			//按键定时扫描
	*/	
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除计数器中断标志
		
	}	


}
