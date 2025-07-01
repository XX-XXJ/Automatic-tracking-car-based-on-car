#ifndef __MOTOR_H__
#define __MOTOR_H__

/*----------- ������Ŷ��� -----------*/
sbit INA = P2^1;   // �������� A
sbit INB = P2^2;   // �������� B
sbit INA2 = P2^3;  // �ҵ������ A
sbit INB2 = P2^4;  // �ҵ������ B

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