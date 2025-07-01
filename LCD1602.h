#ifndef __LCD1602_H__
#define __LCD1602_H__

#include <REGX52.H>
#include <intrins.h>  // 提供 _nop_()

// === 引脚定义 ===
sbit LCD_RS = P0^4;
sbit LCD_RW = P0^3;
sbit LCD_EN = P0^2;


#define delayNOP() {_nop_(); _nop_(); _nop_(); _nop_();}  // 约延时4us

// === 函数声明 ===
void LCD_Init(void);                                     // 初始化LCD
void lcd_wcmd(unsigned char cmd);                        // 写指令
void lcd_wdat(unsigned char dat);                        // 写数据
bit  lcd_busy(void);                                     // 忙检测
void lcd_set_cursor(unsigned char line, unsigned char col);  // 设置光标位置
void LCD_ShowString(unsigned char line, unsigned char col, char *str);  // 显示字符串
void LCD_ShowChar(unsigned char Line, unsigned char Column, char Char);
void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length);

#endif
