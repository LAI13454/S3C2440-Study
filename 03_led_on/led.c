
int main(void)
{
    unsigned int * pGPFCON = (unsigned int *)0x56000050;
    unsigned int * pGPFDAT = (unsigned int *)0x56000054;
    
    *pGPFCON = 0x100;
    *pGPFDAT = 0;
    return 0; 
}
