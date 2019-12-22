#include "stm32f10x.h"
#include "wifi.h"
#include "led.h"
/*串口2连接友人WIFI模块 RXD->PA3 TXD->PA2
波特率推荐96000
无os系统宏定义
支持通讯协议（HTTP,UDP/TCP）
*/
#if EN_USART2_RX   //如果使能了接收
//中断服务函数
//串口2中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   
u8 USART2_RX_BUF[USART2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART2_RX_STA=0;       //接收状态标记	  
extern u8 flag_send;
u8 USART2_RX_BUF[USART2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u8 rec;
void WIFI_init(u32 bound)
{
	
	GPIO_InitTypeDef GPIO_Initstrue;			//GPIO初始化结构体
		USART_InitTypeDef USART_Initstrue;		//USART2初始化结构体
	NVIC_InitTypeDef NVIC_Initstrue;            //NVIC初始化结构体

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //串口2时钟使能  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//串口2引脚TX,RX(PA2,PA3)时钟使能
	
	GPIO_Initstrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Initstrue.GPIO_Pin=GPIO_Pin_2;
	GPIO_Initstrue.GPIO_Speed=GPIO_Speed_50MHz;    //串口2TX （PA2）要设为推挽复用
	//PA9初始化结构体成员变量赋值
	GPIO_Init(GPIOA,&GPIO_Initstrue);
	
		GPIO_Initstrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Initstrue.GPIO_Pin=GPIO_Pin_3;
	GPIO_Initstrue.GPIO_Speed=GPIO_Speed_50MHz;    //串口2RX( PA3)要设为浮空输入或上拉输入
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
	NVIC_Initstrue.NVIC_IRQChannelPreemptionPriority=2;    //抢占优先级为1
	NVIC_Initstrue.NVIC_IRQChannelSubPriority=0;			//响应优先级为3
	//NVIC初始化结构体成员变量赋值
	NVIC_Init(&NVIC_Initstrue);

}

void USART2_IRQHandler(void)  
{

if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //接受缓存区非空 (接收到的数据必须是0x0d 0x0a结尾)
{
	
	
	
	u8 Res;

	
		Res=USART_ReceiveData(USART2);	//读取接收到的数据
		
		if((USART2_RX_STA&0x8000)==0)//接收未完成
			{
				
			if(USART2_RX_STA&0x4000)//接收到了0x0d
				{
					
				if(Res!=0x0a)USART2_RX_STA=0;//接收错误,重新开始
				else USART2_RX_STA|=0x8000;	//接收完成了 
				}
			else //还没收到0X0D
				{	
				if(Res==0x0d)USART2_RX_STA|=0x4000;
				else
					{
					
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}   
		
	

}
}

void Usart_SendString(USART_TypeDef* USARTx,char *str)
{
while(*str)
{
 while(!USART_GetFlagStatus(USARTx,USART_FLAG_TXE)); //判断是否可以发送
      USART_SendData(USARTx,*str);
      while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)); //判断是否发送完成，此句必须有，否则会造
                                                                                                  //成只发送最后一个字符（覆盖）
 str++;           
  }
}


#endif


