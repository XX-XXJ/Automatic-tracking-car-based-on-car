#ifndef __SENSOR_H__
#define __SENSOR_H__

// 红外传感器引脚
sbit Left_LED = P1^5;			
sbit Mid_LED = P1^6;//中间
sbit Right_LED = P1^7;
//位移偏差
extern float err;

// 初始化红外传感器端口
void Sensor_Init(void);

// 读取红外位置偏差（返回值为误差）
float Sensor_GetError(void);

#endif
