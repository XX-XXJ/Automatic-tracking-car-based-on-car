#include <REGX52.H>
#include "MOTOR.h"
#include "SENSOR.h"
#include "PID.h"
#include "TIMER.h"
#include "UART.h"
#include "Delay.h"
#include "LCD1602.h"

sbit KeyStart = P3^7;// 定义启动按键

unsigned char PWM_Count = 0;
float target_speed = 200;
float urge_speed = 100;
float err,output;

unsigned char display_count = 0;

void main()
{
    UART_Init();
    Motor_Init();
    Sensor_Init();
    PID_Init(80.0, 0.01, 5.0);
		LCD_Init();
    EA=1;
		TR0=0;
    UART_SendString("Bluetooth Control Car Ready\r\n");
    UART_SendString("Commands:\r\n");
    UART_SendString("S: Start Motor\r\n");
    UART_SendString("P: Stop Motor (Keep Speed Setting)\r\n");
    UART_SendString("1: Set Speed 40%\r\n");
    UART_SendString("2: Set Speed 60%\r\n");
    UART_SendString("3: Set Speed 100%\r\n");

		while(1)
		{
			// 等待按键按下（带消抖）
			if(KeyStart == 0)  // 按键按下
			{
				Delay(20); // 消抖
				if(KeyStart == 0)
				{
					Timer0_Init();     // 启动定时器
					break;
				}
			}
		}
    while(1)
		{

		}// 空循环，控制在中断中完成
}

void Timer0_ISR(void) interrupt 1
{
    TL0 = 0xA4;
    TH0 = 0xFF;
    PWM_Count++;
    PWM_Count %= 100;

    err = Sensor_GetError();
    output = PID_Compute(err);
		if(err >= 4 || err <= -4) 
				Motor_SetSpeed(urge_speed + output, urge_speed - output);
		else
				Motor_SetSpeed(target_speed + output, target_speed - output);
    Motor_PWM_Control(PWM_Count);
    // 每 100 个中断（约 100ms）刷新一次 LCD 显示
    display_count++;
    if(display_count >= 100)
    {
        display_count = 0;
				LCD_ShowSpeed((int)(Lspeed * 15.0 + 0.5), (int)(Rspeed * 15.0 + 0.5));
    }
}
