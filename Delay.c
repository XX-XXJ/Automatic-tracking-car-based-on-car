
void Delay(unsigned int ms)  // ºÚµ•—” ±
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