#include <REGX52.H>
#include "MOTOR.h"

float Lspeed=0;
float Rspeed=0;

/*--------------------------------------------------
 电机停止函数（所有引脚拉低）
--------------------------------------------------*/
void Motor_Stop(void)
{
    INA = 0;
    INB = 0;
    INA2 = 0;
    INB2 = 0;
}

/*--------------------------------------------------
 电机初始化函数
--------------------------------------------------*/
void Motor_Init(void)
{
    Motor_Stop();  // 启动前先停止电机
}

/*--------------------------------------------------
 设置左右电机速度（单位：-100 ~ 100）
 正值：正转，负值：反转，0：停止
--------------------------------------------------*/
void Motor_SetSpeed(float left, float right)
{
    if(left > 255) left = 255;
    if(left < -255) left = -255;
    if(right > 255) right = 255;
    if(right < -255) right = -255;

    Lspeed = left;
    Rspeed = right;
}


/*--------------------------------------------------
 PWM占空比控制（在定时器中断中调用）
 参数：pwm_count 为 0 ~ 99 的占空比计数器
--------------------------------------------------*/
void Motor_PWM_Control(unsigned char pwm_count)
{
    // 左电机
    if(Lspeed > 0)
    {
        if(pwm_count < Lspeed)
        {
            INA = 1;
            INB = 0;
        }
        else
        {
            INA = 0;
            INB = 0;
        }
    }
    else
    {
        if(pwm_count < -Lspeed)
        {
            INA = 0;
            INB = 1;
        }
        else
        {
            INA = 0;
            INB = 0;
        }
    }

    // 右电机
    if(Rspeed > 0)
    {
        if(pwm_count < Rspeed)
        {
            INA2 = 1;
            INB2 = 0;
        }
        else
        {
            INA2 = 0;
            INB2 = 0;
        }
    }
    else
    {
        if(pwm_count < -Rspeed)
        {
            INA2 = 0;
            INB2 = 1;
        }
        else
        {
            INA2 = 0;
            INB2 = 0;
        }
    }
}