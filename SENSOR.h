#ifndef __SENSOR_H__
#define __SENSOR_H__

// ���⴫��������
sbit Left_LED = P1^5;			
sbit Mid_LED = P1^6;//�м�
sbit Right_LED = P1^7;
//λ��ƫ��
extern float err;

// ��ʼ�����⴫�����˿�
void Sensor_Init(void);

// ��ȡ����λ��ƫ�����ֵΪ��
float Sensor_GetError(void);

#endif
