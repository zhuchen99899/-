#include <Delay.h>
#include<string.h>
#include<stdio.h>
#include<intrins.h>
unsigned int i;
void delay17us(void)
{
unsigned char i;

	i = 44;
	while (--i);

}

void  delay77ms(void)
{


	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 4;
	j = 61;
	k = 84;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);

}


void Delay15ms(void)		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 1;
	j = 162;
	k = 89;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void Delay5ms(void)		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 54;
	j = 198;
	do
	{
		while (--j);
	} while (--i);
}

void Delay400ms(void)		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 17;
	j = 208;
	k = 27;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void Delay500ms(void)		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay1000ms(void)		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay300ms(void)		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 13;
	j = 156;
	k = 83;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}




