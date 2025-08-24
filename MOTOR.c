#include <REGX52.H>
#include "MOTOR.h"

float Lspeed=0;
float Rspeed=0;

/*--------------------------------------------------
 ���ֹͣ�����������������ͣ�
--------------------------------------------------*/
void Motor_Stop(void)
{
    INA = 0;
    INB = 0;
    INA2 = 0;
    INB2 = 0;
}

/*--------------------------------------------------
 �����ʼ������
--------------------------------------------------*/
void Motor_Init(void)
{
    Motor_Stop();  // ����ǰ��ֹͣ���
}

/*--------------------------------------------------
 �������ҵ���ٶȣ���λ��-100 ~ 100��
 ��ֵ����ת����ֵ����ת��0��ֹͣ
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
 PWMռ�ձȿ��ƣ��ڶ�ʱ���ж��е��ã�
 ������pwm_count Ϊ 0 ~ 99 ��ռ�ձȼ�����
--------------------------------------------------*/
void Motor_PWM_Control(unsigned char pwm_count)
{
    // ����
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

    // �ҵ��
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