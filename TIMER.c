#include <REGX52.H>

void Timer0_Init(void)
{
    TMOD &= 0xF0;      // �����ʱ��0λ
    TMOD |= 0x01;      // ����Ϊģʽ1��16λ��
    TL0 = 0xA4;        // 100us ��װֵ@11.0592MHZ
    TH0 = 0xFF;
    TF0 = 0;
    TR0 = 1;
    ET0 = 1;
    EA = 1;
		PT0 = 0;
}
