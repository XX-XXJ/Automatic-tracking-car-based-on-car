#ifndef __SENSOR_H__
#define __SENSOR_H__

// ���⴫��������
sbit Left_LED = P0^1;
sbit Mid_LED  = P0^5;
sbit Right_LED= P0^6;
//λ��ƫ��
extern float err;

// ��ʼ�����⴫�����˿�
void Sensor_Init(void);

// ��ȡ����λ��ƫ�����ֵΪ��
float Sensor_GetError(void);

#endif
