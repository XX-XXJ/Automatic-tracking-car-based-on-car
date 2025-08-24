#include "PID.h"

float Kp = 0, Ki = 0, Kd = 0;
float integral = 0;
float prev_error = 0;
float p,i,d;

void PID_Init(float kp, float ki, float kd)
{
    Kp = kp;
    Ki = ki;
    Kd = kd;
    PID_Reset();
}

void PID_Reset(void)
{
    integral = 0;
    prev_error = 0;		
}

float PID_Compute(float error)
{
    p = Kp * error;
    i = Ki * integral;
    d = Kd * (error - prev_error);
		if(i>10) i = 10; //»ı·ÖÏŞ·ù
    prev_error = error;
    integral += error;
    return p + i + d;
}
