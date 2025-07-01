#include <REGX52.H>
#include "MOTOR.h"
#include "SENSOR.h"
#include "PID.h"
#include "TIMER.h"
#include "UART.h"
#include "Delay.h"
#include "LCD1602.h"

unsigned char PWM_Count = 0;
float target_speed = 80;
float err,output;



void Display(float a, float b)
{		
		int l_int;
		int r_int;
		l_int = (int)(a * 10);
		r_int = (int)(b * 10);
    // === ��ʾ���ٶ� ===
    LCD_ShowString(1, 1, "LSpeed:      ");  // �����㹻��λ
    if (l_int < 0)
    {
        LCD_ShowChar(1, 8, '-');
        l_int = -l_int;
    }
    else
    {
        LCD_ShowChar(1, 8, '+');
    }

    LCD_ShowNum(1, 9, l_int / 10, 2);   // ��������
    LCD_ShowChar(1, 11, '.');
    LCD_ShowNum(1, 12, l_int % 10, 1);  // С������

    // === ��ʾ���ٶ� ===
    LCD_ShowString(2, 1, "RSpeed:      ");
    if (r_int < 0)
    {
        LCD_ShowChar(2, 8, '-');
        r_int = -r_int;
    }
    else
    {
        LCD_ShowChar(2, 8, '+');
    }

    LCD_ShowNum(2, 9, r_int / 10, 2);
    LCD_ShowChar(2, 11, '.');
    LCD_ShowNum(2, 12, r_int % 10, 1);
}


void main()
{
    UART_Init();
    Motor_Init();
    Sensor_Init();
    PID_Init(60.0, 0.02, 2.0);
		LCD_Init();
    EA=0;
		TR0=0;
	
		
		while(1)
		{
			// �ȴ��������£���������
			if(P3^7 == 0)  // ��������
			{
				Delay(20); // ����
				if(P3^7 == 0)
				{
					Timer0_Init();     // ������ʱ��
					break;
				}
			}
		}
    while(1)
		{
			Display(Lspeed,Rspeed);
		}// ��ѭ�����������ж������
}

void Timer0_ISR(void) interrupt 1
{
    TL0 = 0xA4;
    TH0 = 0xFF;
    PWM_Count++;
    PWM_Count %= 80;

    err = Sensor_GetError();
    output = PID_Compute(err);

    Motor_SetSpeed(target_speed + output, target_speed - output);
    Motor_PWM_Control(PWM_Count);

}
