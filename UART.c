#include <REGX52.H>
#include "UART.h"
#include <stdio.h>

/**
  * @brief  ���ڳ�ʼ����4800bps@12.000MHz
  * @param  ��
  * @retval ��
  */
void UART_Init(void)
{
    // ���ڿ��ƼĴ�������
    SCON = 0x50;        // 8λ����λ���ɱ䲨���ʣ��������
    
    // �����ʼӱ�����
    PCON |= 0x80;       // SMOD=1 (�����ʼӱ�)
    
    // ��ʱ��1ģʽ����
    TMOD &= 0x0F;       // �����ʱ��1ģʽλ
    TMOD |= 0x20;       // ��ʱ��1������ģʽ2 (8λ�Զ���װ)
    
    // ���������� (9600 bps @ 115200MHz)
        TL1 = 0xFA;     // ��ʱ��ֵ
        TH1 = 0xFA;     // ��װֵ
    
    // ��ʱ������
    ET1 = 0;            // ��ֹ��ʱ��1�ж�
    TR1 = 1;            // ������ʱ��1
    
    // �����ж�ʹ�ܣ��������Ҫ���չ��ܣ�����ע�͵���
//     ES = 1;           // ʹ�ܴ����ж�
//     EA = 1;           // �������ж�
}

/**
  * @brief  ���ڷ���һ���ֽ�����
  * @param  Byte Ҫ���͵������ֽ�
  * @retval ��
  */

void UART_SendByte(unsigned char Byte)
	
{
		SBUF = Byte;
		while(TI == 0);
		TI = 0;
}

/**
  * @brief  �����ַ���
  * @param  str Ҫ���͵��ַ���ָ��
  * @retval ��
  */
void UART_SendString(char *str)
{
    while(*str != '\0') {
        UART_SendByte(*str++);
    }
}

/**
  * @brief  ���������� (0-65535)
  * @param  num Ҫ���͵�������
  * @retval ��
  */
void UART_SendNumber(unsigned int num)
{
    char buffer[6];     // �洢ת����������ַ���
    unsigned char i = 0;
    unsigned int temp = num;
    
    // ����0���������
    if (num == 0) {
        UART_SendByte('0');
        return;
    }
    
    // ��ȡÿһλ����
    while (temp > 0) {
        buffer[i++] = (temp % 10) + '0';
        temp /= 10;
    }
    
    // ��ת����������
    while (i > 0) {
        UART_SendByte(buffer[--i]);
    }
}

// �����Ҫ���չ��ܣ���ȡ��ע�Ͳ�ʵ���жϷ�����
/*
void UART_Routine(void) interrupt 4
{
    if(RI) {
        RI = 0;         // ��������жϱ�־
        // �������ݴ���������������
        // unsigned char received = SBUF;
    }
}
*/