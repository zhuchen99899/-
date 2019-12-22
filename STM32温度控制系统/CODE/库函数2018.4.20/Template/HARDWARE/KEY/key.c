#include "stm32f10x.h"
#include "key.h"
#include "delay.h"

void key_init(void)
{
	
	GPIO_InitTypeDef   GPIO_InitStructure;//定义结构体用于输入输出设置
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE); //rcc时钟使能PE口
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//rcc时钟使能PA口
	
	


	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//结构体赋值
	GPIO_Init(GPIOE,&GPIO_InitStructure);//PE4口 key0 设置为上拉输入
	


	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//结构体赋值
	GPIO_Init(GPIOE,&GPIO_InitStructure);//PE3口 key1 设置位上拉输入
	

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//结构体赋值
	GPIO_Init(GPIOE,&GPIO_InitStructure);//PE2口 key2 设置位上拉输入
	

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//结构体赋值
	GPIO_Init(GPIOA,&GPIO_InitStructure);//PA0口 key3 设置位下拉输入
	
}


 u8 KEY_SCAN(u8 mode)
{
static u8 key_up=1;//按键松开标志
	
if(mode) key_up=1;//支持连按
	if(key_up&&(KEY1==0||KEY2==0))
		
	{
	delay_ms(10);
	key_up=0;

		if(KEY1==0) return KEY1_PRESS;
		if(KEY2==0) return KEY2_PRESS;
	
	} else if (KEY1==1&&KEY2==1)key_up=1;
return 0;
}



