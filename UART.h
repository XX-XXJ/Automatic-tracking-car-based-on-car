#ifndef __UART_H__
#define __UART_H__

// 硬件平台选择 (默认使用STC89C52)
// #define FOSC 12000000L  // 晶振频率定义

void UART_Init(void);
void UART_SendByte(unsigned char Byte);
void UART_SendString(char *str);
void UART_SendNumber(unsigned int num);
// 钃濈墮鎺у埗鐩稿叧鍑芥暟
void Bluetooth_Control(unsigned char cmd);
#endif