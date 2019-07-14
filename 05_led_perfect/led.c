
void delay(unsigned int a)
{
    while (a--);
}

int main(void)
{
    unsigned char val = 0, temp;

    unsigned int * pGPFCON = (unsigned int *)0x56000050;
    unsigned int * pGPFDAT = (unsigned int *)0x56000054;
    
    /*LED1(GPF6) LED2(GPF5) LED3(GPF4) */
    *pGPFCON &= ~((3 << 12) | (3 << 10) | (3 << 8));
    *pGPFCON |= ((1 << 12) | (1 << 10) | (1 << 8));

    while (1)
    {
        temp = ~val;
        temp &= 0x07;
        *pGPFDAT = (temp << 4);
        delay(100000);
        val ++;
        if(val == 8)
        {
            val = 0;
        }
    }
    
    *pGPFDAT = 0;
    return 0; 
}
