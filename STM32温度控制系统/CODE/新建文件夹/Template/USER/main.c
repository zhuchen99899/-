#include "stm32f10x.h"
#include "delay.h"
#include "lcd.h"
#include "pwm.h"
#include "led.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "adc.h"
#include "tem.h"
#include "pid.h"



	 float ADC1_tem=0;
	 
 	int main(void)
 {	 	float temp=0;
	 
	 float tp=0;
	 float dr=0;
	 float res=0;
	 
	 float getadcx[14];      //存储15个adc值
	 float adctemp=0;
	 float t=0;
	 float receive=0;
float try;
	 int Keytem=0;
	 int a=0;
	 int b=0;
	 int i;
	 int j=0;
	 vu8 key=0;	
	 	 
     u16 adcx;
	 u16 led0pwmval=720;
	 u16 test;
	 u16 ADC1_du;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化
	LCD_Init();			 	
 	Adc_Init();		  		//ADC初始化
		 key_init();
		 pid_init();        //PID初始化
TIM3_PWM_Init(1439,0);//1439+1=1440,不分频，频率为72000000/1440=50khz
	 

	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"graduation project：temperature-control system");	
	LCD_ShowString(60,70,200,16,16,"author:zhuchen");	
	LCD_ShowString(60,90,200,16,16,"14 Electrical Engineering and Automation");
	LCD_ShowString(60,110,200,16,16,"2018/4/5");	
	//显示提示信息
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60,130,200,16,16,"ADC_CH0_VAL:");	      
	LCD_ShowString(60,150,200,16,16,"ADC_CH0_VOL:0.000V");	
LED1=0;	
	while(1)
	{
		key=KEY_SCAN(1);
		if(key)
		{
		switch (key)
			{
			case KEY1_PRESS:
				 led0pwmval+=1;
			break;
			case KEY2_PRESS:
				led0pwmval-=1;
			break;
			}
		
		}else delay_ms(10);
			if(led0pwmval>1439)led0pwmval=350;
		    else if(led0pwmval<0) led0pwmval=0;
		LCD_ShowString(60,170,200,16,16,"Tempreture:");
		LCD_ShowxNum(145,170,Keytem,3,16,0);
	
	
		
		
		adcx=Get_Adc_Average(ADC_Channel_1,10);
		LCD_ShowxNum(156,130,adcx,4,16,0);//显示ADC的值


		for(j=0;j<14;j++)              //取14次ADC值 存储到getadcx数组
		{
			
		temp=(float)adcx*(3.0/4096); //STM32是12位的ADC ,2的12次方=4096
		getadcx[j]=temp;
		}                    


		for(a=0;a<14;a++)       //冒泡排序
		{
     		for(b=0;b<13;b++)
			{
				
				if(getadcx[b]>getadcx[b+1])
				{

			adctemp=getadcx[b];
			getadcx[b+1]=getadcx[b];
			getadcx[b]=adctemp;

				}
			}

		}

		for(i=2;i<11;i++)    //算数滤波，去除两个最大值和两个最小值，然后求和
		{
		t+=getadcx[i];
		}
		t=t/10               ;        //取平均值
		
		
		
		temp=t;
		 
		receive=t;
		
		adcx=temp;//adcx为整型 temp为float浮点数型，将temp赋值给adcx只取整数
		LCD_ShowxNum(156,150,adcx,1,16,0);//显示电压值 （整数部分）
		temp-=adcx; //temp=temp-adcx 减去电压整数部分
		temp*=1000;//temp=temp*1000 将小数变为整数 精确到3位小数
		LCD_ShowxNum(172,150,temp,3,16,0X80); //显示电压值（小数部分）
		
		res=((receive/10.0)/0.909)*1000.0;
		
		ADC1_tem=(int)get_tem(res);
	
				LCD_ShowString(60,190,200,16,16,"ActureTempretureFromADC1:");
	

		LCD_ShowxNum(320,190,ADC1_tem,3,16,0);
		
		/*
		 led0pwmval=pid_realize(Keytem);
		*/
		
		TIM_SetCompare2(TIM3,led0pwmval);//PWM输出
		
		LCD_ShowString(60,210,200,16,16,"PWMVAL:");
		LCD_ShowxNum(150,210,led0pwmval,4,16,0);
/*		
		dr=(1-(led0pwmval/1800))*100;
		LCD_ShowString(60,230,200,16,16,"Duty Ratio:");
		LCD_ShowxNum(150,230,dr,3,16,0);
	*/	
LCD_Draw_Circle(400,600,40);
delay_ms(100);
	
	}
}
 


 