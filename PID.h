#ifndef __PID_H__
#define __PID_H__



void PID_Init(float kp, float ki, float kd);
void PID_Reset(void);
float PID_Compute(float error);  // ·µ»ØÊä³öÖµ

#endif
