#include <REGX52.H>

void Timer0_Init(void)
{
    TMOD &= 0xF0;      // 清除定时器0位
    TMOD |= 0x01;      // 设置为模式1（16位）
    TL0 = 0xA4;        // 100us 重装值@11.0592MHZ
    TH0 = 0xFF;
    TF0 = 0;
    TR0 = 1;
    ET0 = 1;
    EA = 1;
		PT0 = 0;
}
