
void Delay(unsigned int ms)  // ����ʱ
{
    unsigned char i, j;
    while(ms--)
    {
        i = 2;
        j = 199;
        do {
            while (--j);
        } while (--i);
    }
}