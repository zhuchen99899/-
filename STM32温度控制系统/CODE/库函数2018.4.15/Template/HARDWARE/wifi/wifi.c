#include "stm32f10x.h"
#include "wifi.h"
/*串口2连接友人WIFI模块 RXD->PA3 TXD->PA2
波特率推荐96000
无os系统宏定义
支持通讯协议（HTTP,UDP/TCP）
*/

void WIFI_init(u32 bound)
{
	
	GPIO_InitTypeDef GPIO_Initstrue;			//GPIO初始化结构体
		USART_InitTypeDef USART_Initstrue;		//USART2初始化结构体
	NVIC_InitTypeDef NVIC_Initstrue;            //NVIC初始化结构体
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //串口2时钟使能 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//串口2引脚TX,RX(PA2,PA3)时钟使能
	
	GPIO_Initstrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Initstrue.GPIO_Pin=GPIO_Pin_2;
	GPIO_Initstrue.GPIO_Speed=GPIO_Speed_10MHz;    //串口2TX （PA2）要设为推挽复用
	//PA9初始化结构体成员变量赋值
	GPIO_Init(GPIOA,&GPIO_Initstrue);
	
		GPIO_Initstrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Initstrue.GPIO_Pin=GPIO_Pin_3;
	GPIO_Initstrue.GPIO_Speed=GPIO_Speed_10MHz;    //串口1RX( PA3)要设为浮空输入或上拉输入
	//PA10初始化结构体成员变量赋值
	GPIO_Init(GPIOA,&GPIO_Initstrue);
	

	USART_Initstrue.USART_BaudRate=115200;									//波特率115200
	USART_Initstrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //无硬件流控制
	USART_Initstrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;		//输入输出模式
	USART_Initstrue.USART_Parity=USART_Parity_No;		 		//无奇偶校验位
	USART_Initstrue.USART_StopBits=USART_StopBits_1;			//1个停止位
	USART_Initstrue.USART_WordLength=USART_WordLength_8b;       //数据长度为8位
	//串口初始化结构体成员变量赋值
	
	USART_Init(USART2,&USART_Initstrue);
	
	USART_Cmd(USART2,ENABLE);           //使能串口2
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);   //开启串口2接收中断，中断类型：接受缓存器非空（接受到数据时产生中断）
	
	
	NVIC_Initstrue.NVIC_IRQChannel=USART2_IRQn;				//中断通道为串口2中断
	NVIC_Initstrue.NVIC_IRQChannelCmd=ENABLE;				//通道使能
	NVIC_Initstrue.NVIC_IRQChannelPreemptionPriority=1;    //抢占优先级为1
	NVIC_Initstrue.NVIC_IRQChannelSubPriority=3;			//响应优先级为3
	//NVIC初始化结构体成员变量赋值
	NVIC_Init(&NVIC_Initstrue);

}

void USART2_IRQHandler(void)  
{
u8 rx;
if(USART_GetITStatus(USART2,USART_IT_RXNE)) //接受缓冲区非空
{

rx=USART_ReceiveData(USART2);
	
}

}


