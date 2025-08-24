#ifndef __UART_H__
#define __UART_H__

// Ӳ��ƽ̨ѡ�� (Ĭ��ʹ��STC89C52)
// #define FOSC 12000000L  // ����Ƶ�ʶ���

void UART_Init(void);
void UART_SendByte(unsigned char Byte);
void UART_SendString(char *str);
void UART_SendNumber(unsigned int num);
// 蓝牙控制相关函数
void Bluetooth_Control(unsigned char cmd);
#endif