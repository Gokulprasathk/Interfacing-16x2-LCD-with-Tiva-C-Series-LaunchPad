
#include<TM4C123GH6PM.h>
#include<stdio.h>
void delay();
void print_data(unsigned char data);
void lcd_data(unsigned char data);
void lcd_cmd(unsigned char cmd);
void lcd_string(unsigned char *str,unsigned char len);
void lcd_init(void);

int main(void)
{
	
	//clock for gpio ports
	
	SYSCTL->RCGCGPIO |=(1<<0)|(1<<1)|(1<<3)|(1<<4);
	
	//digitalise the gpio ports
	
	GPIOA->DEN |=(1<<5)|(1<<6)|(1<<7);
	GPIOB->DEN |=(1<<0)|(1<<1)|(1<<4);
	GPIOD->DEN |=(1<<0)|(1<<1)|(1<<2);
	GPIOE->DEN |=(1<<4) |(1<<5);
	
	//input /output port for gpio 
	
	GPIOA->DIR |=(1<<5)|(1<<6)|(1<<7);
	GPIOB->DIR |=(1<<0)|(1<<1)|(1<<4);
	GPIOD->DIR |=(1<<0)|(1<<1)|(1<<2);
	GPIOE->DIR |=(1<<4) |(1<<5);
	
	delay();
	lcd_init();
	lcd_data('a');
	while(1);
	
}

void lcd_data(unsigned char data)
{ 
	print_data(data);
	GPIOD->DATA |=(1<<0);
	GPIOD->DATA &= (~(1<<1));
	GPIOD->DATA |=(1<<2);
	delay();
	GPIOD->DATA &=(~(1<<2));
	
	
	
}

void lcd_cmd(unsigned char cmd)
{
	print_data(cmd);
	GPIOD->DATA &=(~(1<<0));
	GPIOD->DATA &= (~(1<<1));
	GPIOD->DATA |=(1<<2);
	delay(10000);
	GPIOD->DATA &=(~(1<<2));
	
	
	
}


void print_data(unsigned char data)
{
	
	if((data & 0x01) ==0x01)        {GPIOA->DATA |=(1<<0);}
	else                            {GPIOA->DATA &=(~(1<<0));}
	if((data & 0x02) ==0x02)        {GPIOA->DATA |=(1<<1);}
	else                            {GPIOA->DATA &=(~(1<<1));}
	if((data & 0x04) ==0x04)        {GPIOA->DATA |=(1<<2);}
	else                            {GPIOA->DATA &=(~(1<<2));}
	if((data & 0x08) ==0x08)        {GPIOB->DATA |=(1<<3);}
	else                            {GPIOB->DATA &=(~(1<<3));}
	if((data & 0x10) ==0x10)        {GPIOE->DATA |=(1<<4);}
	else                            {GPIOE->DATA &=(~(1<<4));}
	if((data & 0x20) ==0x20)        {GPIOE->DATA |=(1<<5);}
	else                            {GPIOE->DATA &=(~(1<<5));}
	if((data & 0x40) ==0x40)        {GPIOB->DATA |=(1<<6);}
	else                            {GPIOB->DATA &=(~(1<<6));}
	if((data & 0x80) ==0x80)        {GPIOB->DATA |=(1<<7);}
	else                            {GPIOB->DATA &=(~(1<<7));}
	
}

void lcd_init(void)
{
	lcd_cmd(0x38);
	lcd_cmd(0x06);
	lcd_cmd(0x0C);
	lcd_cmd(0x01);
}
	


void delay()
{  unsigned int i,j,k;
	for(i=0;i<0xff;i++);
	 for(j=0;j<0xff;j++);	
}


void lcd_string(unsigned char *str,unsigned char len)
{
	int i;
	for(i=0;i<len;i++)
	{
		lcd_data(str[i]);
	}
	
}

