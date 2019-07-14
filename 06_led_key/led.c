#include "s3c2440_soc.h"

void delay(unsigned int a)
{
    while (a--);
}

int main(void)
{
    /* LED1(GPF6) LED2(GPF5) LED3(GPF4) */
    GPFCON &= ~((3 << 12) | (3 << 10) | (3 << 8));
    GPFCON |= ((1 << 12) | (1 << 10) | (1 << 8));

    /* EINT0(GPF0) EINT2(GPF2) EINT11(GPG3) */
    GPFCON &= ~((3 << 0) | (3 << 4));
    GPGCON &= ~(3 << 6);


    while (1)
    {
        if(GPFDAT & (1 << 0))
        {
            GPFDAT |= (1 << 6);
        }
        else
        {
            GPFDAT &= ~(1 << 6);
        }

        if(GPFDAT & (1 << 2))
        {
            GPFDAT |= (1 << 5);
        }
        else
        {
            GPFDAT &= ~(1 << 5);
        }

        if(GPGDAT & (1 << 3))
        {
            GPFDAT |= (1 << 4);
        }
        else
        {
            GPFDAT &= ~(1 << 4);
        }
        
    }
    return 0; 
}
