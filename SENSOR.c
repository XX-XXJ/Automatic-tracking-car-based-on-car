#include <REGX52.H>
#include "SENSOR.h"


void Sensor_Init(void)
{
    P0 |= 0x0E;  // P0.1 ~ P0.3 设置为输入模式
}

// 返回位置误差（-2.5 ~ 2.5）
float Sensor_GetError(void)
{
    unsigned char L = Left_LED;
    unsigned char M = Mid_LED;
    unsigned char R = Right_LED;
    err = 0;

    if(L == 0 && M == 1 && R == 0)      err = 0;
    else if(L == 1 && M == 1 && R == 0) err = -1;
    else if(L == 1 && M == 0 && R == 0) err = -2.5;
    else if(L == 0 && M == 1 && R == 1) err = 1;
    else if(L == 0 && M == 0 && R == 1) err = 2.5;
    else                                err = 0; // 全黑或全白默认中线

    return err;
}
