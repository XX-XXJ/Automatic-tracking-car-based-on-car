#include "LCD1602.h"

//bit lcd_busy()//���LCD�Ƿ�æ
//{
//	bit result;
//	LCD_RS = 0;
//	LCD_RW = 1;
//	LCD_EN = 1;//��������˶�ָ��״̬
//	delayNOP();//��ʱ4us
//	result=(bit)(P2&0x80);
//	LCD_EN = 0;
//	return result;

//}

void lcd_wcmd(unsigned char cmd)
	{
//		while(lcd_busy()==1);
		LCD_RS = 0;
		LCD_RW = 0;
		LCD_EN = 0;
		_nop_();
		_nop_();
		P2 = cmd;
		delayNOP();//��ʱ4us
		LCD_EN = 1;
		delayNOP();//��ʱ4us
		LCD_EN = 0;
	
	}

void lcd_init()
{
	lcd_wcmd(0x38);  // 8λ���ݣ�2�У�5��7����
	lcd_wcmd(0x0C);  // ����ʾ������ʾ���
	lcd_wcmd(0x06);  // д��������ʱ�������
	lcd_wcmd(0x01);  // ����
}

void lcd_wdat(unsigned char dat)
{
//	while(lcd_busy() == 1); // �ȴ�LCD����
	LCD_RS = 1;  // д����ģʽ
	LCD_RW = 0;  // д
	LCD_EN = 0;
	_nop_(); _nop_(); // С��ʱ
	P2 = dat;
	delayNOP();       // ��ʱ 4us
	LCD_EN = 1;
	delayNOP();
	LCD_EN = 0;
}
void lcd_set_cursor(unsigned char line, unsigned char col)
{
	unsigned char address;
	if (line == 1)
		address = 0x80 + (col - 1);      // ��һ�е�ַ��0x80 ~ 0x8F
	else
		address = 0x80 + 0x40 + (col - 1); // �ڶ��е�ַ��0xC0 ~ 0xCF

	lcd_wcmd(address);
}

void LCD_ShowString(unsigned char line, unsigned char col, char *str)
{
	lcd_set_cursor(line, col);
	while (*str != '\0')
	{
		lcd_wdat(*str++);
	}
}

void LCD_ShowChar(unsigned char Line, unsigned char Column, unsigned char Char)
{
    lcd_set_cursor(Line, Column);
    lcd_wdat(Char);
}

int LCD_Pow(int base, int exp)
{
	int result = 1;
	while (exp--)
	{
		result *= base;
	}
	return result;
}

void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i;
	lcd_set_cursor(Line, Column);
	for(i = Length; i > 0; i--)
	{
		lcd_wdat('0' + (Number / LCD_Pow(10, i - 1)) % 10);
	}
}


