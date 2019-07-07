# 工程为学习S3C2440的过程程序
### OPENOCD 配置下载S3C2440
openocd -f interface/ftdi/100ask-openjtag.cfg  -f board/mini2440.cfg  //使用OPENJTAG 和 2440
telnet localhost 4444 
telnet 命令：
reset
init_2440
nand probe 0
nand erase 0 0x0 0xa0000
nand write 0 /Users/lai/Documents/S3C2440/02_led_on_modify_bin/led_on.bin 0
reset

### 01：点亮一个LED
程序中通过设置GPF5的引脚点亮LED，首先配置GPFCON讲PIN5设置为输出模式，再设置GPFDAT，将引脚设置为输出低电平点亮LED
注意：Makefile 因使用TAB换行，不使用空格替换，命令 set noexpandtab
### 02：修改项目1中的bin文件通过修改文件改变点亮灯的位置 GPF6
MOV指令：
1、mov    r3, #0x56000000
虽然0x56000000是一个32位的数，但是可以找到这么一个8位立即数，通过右移得到，看下机器码e3a03456，展开成二进制，对照下格式
1110  0011 1010  0000  0011  0100  0101  0110
cond[31:28]=1110
[27:26]=00
L[25]=1，代表op2是一个立即数
OpCode[24:21]=1101
S[20]=0
Rn[19:16]=0000
Rd[15:12]=0011，R3
Op2[11:8]=0100，右移4 ＊ 2位
Op2[7:0]=0101 0110，8位立即数，0x56
首先要将0x56扩展成32位的无符号数，0x00000056，然后循环右移8位，就得到了0x56000000
