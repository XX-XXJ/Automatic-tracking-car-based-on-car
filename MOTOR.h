#ifndef __MOTOR_H__
#define __MOTOR_H__

/*----------- ������Ŷ��� -----------*/
sbit INA=P1^1;//�����
sbit INB=P1^2;
sbit INA2=P1^3;//�����
sbit INB2=P1^4;

// ����ٶȱ���
extern float Lspeed;
extern float Rspeed;


// �����ʼ�����������ţ�������ѡ
void Motor_Init(void);

// �������ҵ���ٶ� (-100 ~ 100)
void Motor_SetSpeed(float left, float right);

// ���ֹͣ
void Motor_Stop(void);

// ��ʱ���ж��е��õ�PWM���ƺ���
void Motor_PWM_Control(unsigned char pwm_count);

#endif