#include <REGX52.H>
#include "UART.h"
#include <stdio.h>

/**
  * @brief  串口初始化，4800bps@12.000MHz
  * @param  无
  * @retval 无
  */
void UART_Init(void)
{
    // 串口控制寄存器配置
    SCON = 0x50;        // 8位数据位，可变波特率，允许接收
    
    // 波特率加倍控制
    PCON |= 0x80;       // SMOD=1 (波特率加倍)
    
    // 定时器1模式配置
    TMOD &= 0x0F;       // 清除定时器1模式位
    TMOD |= 0x20;       // 定时器1工作于模式2 (8位自动重装)
    
    // 波特率设置 (9600 bps @ 115200MHz)
        TL1 = 0xFA;     // 定时初值
        TH1 = 0xFA;     // 重装值
    
    // 定时器控制
    ET1 = 0;            // 禁止定时器1中断
    TR1 = 1;            // 启动定时器1
    
    // 串口中断使能（如果不需要接收功能，可以注释掉）
//     ES = 1;           // 使能串口中断
//     EA = 1;           // 开启总中断
}

/**
  * @brief  串口发送一个字节数据
  * @param  Byte 要发送的数据字节
  * @retval 无
  */

void UART_SendByte(unsigned char Byte)
	
{
		SBUF = Byte;
		while(TI == 0);
		TI = 0;
}

/**
  * @brief  发送字符串
  * @param  str 要发送的字符串指针
  * @retval 无
  */
void UART_SendString(char *str)
{
    while(*str != '\0') {
        UART_SendByte(*str++);
    }
}

/**
  * @brief  发送正整数 (0-65535)
  * @param  num 要发送的正整数
  * @retval 无
  */
void UART_SendNumber(unsigned int num)
{
    char buffer[6];     // 存储转换后的数字字符串
    unsigned char i = 0;
    unsigned int temp = num;
    
    // 处理0的特殊情况
    if (num == 0) {
        UART_SendByte('0');
        return;
    }
    
    // 提取每一位数字
    while (temp > 0) {
        buffer[i++] = (temp % 10) + '0';
        temp /= 10;
    }
    
    // 反转并发送数字
    while (i > 0) {
        UART_SendByte(buffer[--i]);
    }
}

// 如果需要接收功能，请取消注释并实现中断服务函数
/*
void UART_Routine(void) interrupt 4
{
    if(RI) {
        RI = 0;         // 清除接收中断标志
        // 接收数据处理可以在这里添加
        // unsigned char received = SBUF;
    }
}
*/