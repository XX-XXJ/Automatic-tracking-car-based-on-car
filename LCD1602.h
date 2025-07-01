#ifndef __LCD1602_H__
#define __LCD1602_H__

#include <REGX52.H>
#include <intrins.h>  // �ṩ _nop_()

// === ���Ŷ��� ===
sbit LCD_RS = P0^4;
sbit LCD_RW = P0^3;
sbit LCD_EN = P0^2;


#define delayNOP() {_nop_(); _nop_(); _nop_(); _nop_();}  // Լ��ʱ4us

// === �������� ===
void LCD_Init(void);                                     // ��ʼ��LCD
void lcd_wcmd(unsigned char cmd);                        // дָ��
void lcd_wdat(unsigned char dat);                        // д����
bit  lcd_busy(void);                                     // æ���
void lcd_set_cursor(unsigned char line, unsigned char col);  // ���ù��λ��
void LCD_ShowString(unsigned char line, unsigned char col, char *str);  // ��ʾ�ַ���
void LCD_ShowChar(unsigned char Line, unsigned char Column, char Char);
void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length);

#endif
