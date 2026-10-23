#include<reg51.h>
sbit RS=P1^1;
sbit RW=P1^2;
sbit EN=P1^3;
sbit pump=P1^4;

#define data_line P2
void lcd_string(unsigned char*);
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void delay(void);

void UART_init(void);
void trans(unsigned char);
unsigned char receive(void);


void main()
{
	unsigned char x;
	lcd_init();
	UART_init();
	lcd_cmd(0X80);
	lcd_string("SYSTEM READY");
	pump=0;     //pump is off

	while(1)
	{
		x=receive();
		trans(x);
		if(x=='1')
		{
			pump=1;
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_string("PUMP IS ON");
		}
		else if(x=='0')
		{
			pump=0;
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_string("PUMP IS OFF");
		}
	}
}
void UART_init(void)
{
	TMOD=0X20;
	TH1=0XFD;
	TR1=1;
	SCON=0X50;
}
void trans(unsigned char c)
{
	SBUF=c;
	while(TI==0);
	TI=0;
}
unsigned char receive(void)
{
	while(RI==0);
	RI=0;
	return SBUF;
}
void lcd_init(void)
{
	lcd_cmd(0X30);
	lcd_cmd(0X38);
	lcd_cmd(0X01);
	lcd_cmd(0X80);
	lcd_cmd(0X0F);
}
void lcd_cmd(unsigned char c)
{
	data_line=c;
	RS=0;
	RW=0;
	EN=1;
	delay();
	EN=0;
}
void lcd_data(unsigned char c)
{
	data_line=c;
	RS=1;
	RW=0;
	EN=1;
	delay();
	EN=0;
}
void lcd_string(unsigned char *p)
{
	while(*p!='\0')
	{
		lcd_data(*p);
		p++;
	}
}
void delay(void)
{
	int i,j;
	for(i=0;i<200;i++)
	{
		for(j=0;j<200;j++)
		{
		}
	}
}

