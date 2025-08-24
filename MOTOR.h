#ifndef __MOTOR_H__
#define __MOTOR_H__

/*----------- 电机引脚定义 -----------*/
sbit INA=P1^1;//电机左
sbit INB=P1^2;
sbit INA2=P1^3;//电机右
sbit INB2=P1^4;

// 电机速度变量
extern float Lspeed;
extern float Rspeed;


// 电机初始化（定义引脚）——可选
void Motor_Init(void);

// 设置左右电机速度 (-100 ~ 100)
void Motor_SetSpeed(float left, float right);

// 电机停止
void Motor_Stop(void);

// 定时器中断中调用的PWM控制函数
void Motor_PWM_Control(unsigned char pwm_count);

#endif