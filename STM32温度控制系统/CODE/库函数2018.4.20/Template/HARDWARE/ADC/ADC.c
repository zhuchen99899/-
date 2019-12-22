#include "adc.h"
#include "stm32f10x.h"
#include "delay.h"
void Adc_Init(void)
{
GPIO_InitTypeDef GPIO_InitStrue;
	ADC_InitTypeDef ADC_InitStrue;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE);//GPIOA和ADC1 RCC时钟使能
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Init(GPIOA,&GPIO_InitStrue); //PA1口设置位ADC1模式
	
RCC_ADCCLKConfig(RCC_PCLK2_Div6); //ADC的时钟不能超过14M,PCLK2为72M，至少为6分频
	
	ADC_DeInit(ADC1); //复位ADC1
	
	ADC_InitStrue.ADC_ContinuousConvMode=DISABLE; //不使用连续转换模式
	ADC_InitStrue.ADC_DataAlign=ADC_DataAlign_Right; //数据右对齐模式。STM32是12位ADC，有16位寄存器，12位数据存储右对齐
	ADC_InitStrue.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//不使用外部触发ADC模式。(软件ADC模式）
	ADC_InitStrue.ADC_Mode=ADC_Mode_Independent;//独立ADC模式
	ADC_InitStrue.ADC_NbrOfChannel=1; //单通道ADC
	ADC_InitStrue.ADC_ScanConvMode=DISABLE; //不使用扫描模式
	
	ADC_Init(ADC1,&ADC_InitStrue);//ADC初始化
	
	ADC_Cmd(ADC1,ENABLE);//使能ADC1
	
	//ADC校准
	ADC_ResetCalibration(ADC1); //使能复位校准
	
	while(ADC_GetResetCalibrationStatus(ADC1)); //等待复位校准结束
	
	ADC_StartCalibration(ADC1);//开启AD校准
	
	while(ADC_GetCalibrationStatus(ADC1));//等待AD校准结束
}
u16 Get_Adc (u8 ch)
{
	/*ch 有效性
 ADC_Channel_0                              
 ADC_Channel_1                            
 ADC_Channel_2                           
 ADC_Channel_3                            
 ADC_Channel_4                          
 ADC_Channel_5                         
 ADC_Channel_6                           
 ADC_Channel_7                              
 ADC_Channel_8                         
 ADC_Channel_9                               
 ADC_Channel_10                              
 ADC_Channel_11                            
 ADC_Channel_12                              
 ADC_Channel_13                              
 ADC_Channel_14                             
 ADC_Channel_15                             
 ADC_Channel_16                            
 ADC_Channel_17     
	*/
	ADC_RegularChannelConfig(ADC1,ch,1,ADC_SampleTime_239Cycles5); //规则通道配设：ADC名，第几个通道，rank=此通道在这个规则序列中是第几个转换（只有1个通道所以也只有1次转换），采样时间
	
ADC_SoftwareStartConvCmd(ADC1,ENABLE);//开启软件转换

while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);//等待转换结束

return ADC_GetConversionValue(ADC1); //获取转换值
}
u16 Get_Adc_Average(u8 ch,u8 times)
{

u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
	temp_val+=Get_Adc(ch);
		delay_ms(5);
	
	}


return temp_val/times;
}

