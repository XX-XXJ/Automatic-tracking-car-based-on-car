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
    IP|=0x10;
//    // �����ж�ʹ�ܣ��������Ҫ���չ��ܣ�����ע�͵���
     ES = 1;           // ʹ�ܴ����ж�
     EA = 1;           // �������ж�
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

//// 电机判断开启标志位
//extern bit Motor_Running;
//extern float target_speed;

// 电机控制标志
//extern bit Motor_Running;
extern float target_speed;
//extern float saved_speed;
extern float Rspeed;
extern float Lspeed;
void Bluetooth_Control(unsigned char cmd)
{
    switch(cmd)
    {
        case 'A':   // ����������ָ�֮ǰ���ٶȣ�
            // Motor_Running = 1;
            // target_speed = saved_speed;
            UART_SendString("Motor Started\r\n");
            break;

        case 'B':   // ֹͣ�����ֹͣת�����������ٶ����ã�
            // Motor_Running = 0;
            // saved_speed = target_speed; // ���浱ǰ�ٶ�
            target_speed = 0;             // ��ʱ��Ϊ0
            UART_SendString("Motor Stopped\r\n");
            break;

        case 'C':   // �ٶȵ�λ1��50%��
            target_speed = 50;
            // saved_speed = 50;
            UART_SendString("Speed: 50%\r\n");
            break;

        case 'D':   // �ٶȵ�λ2��80%��
            target_speed = 80;
            // saved_speed = 80;
            UART_SendString("Speed: 80%\r\n");
            break;

        case 'E':   // �ٶȵ�λ3��100%��
            target_speed = 100;
            // saved_speed = 100;
            UART_SendString("Speed: 100%\r\n");
            break;

        default:    // δָ֪��
            UART_SendString("Unknown Command\r\n");
            break;
    }
}


// �����Ҫ���չ��ܣ���ȡ��ע�Ͳ�ʵ���жϷ�����
void UART_Routine(void) interrupt 4
{
	unsigned char received;
    if(RI) {
        RI = 0;  			
        received = SBUF;  // ��ȡ���յ�������
        Bluetooth_Control(received);  // ������������
	}
}