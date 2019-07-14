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

### 03: 通过start.S中调用main函数，点亮LED，启动文件负责设置堆栈指针，堆栈指正解释如下
当从NAND启动时
    cpu会自动从NAND flash中读取前4KB的数据放置在片内SRAM里（s3c2440是soc），同时把这段片内SRAM映射到nGCS0片选的空间（即0x00000000）。cpu是从0x00000000开始执行，也就是NAND flash里的前4KB内容。因为NAND FLASH连地址线都没有，不能直接把NAND映射到0x00000000，只好使用片内SRAM做一个载体。通过这个载体把nandflash中大代码复制到RAM(一般是SDRAM)中去执行。
当从非NAND flash启动时
    nor flash被映射到0x00000000地址（就是nGCS0，这里就不需要片内SRAM来辅助了，所以片内SRAM的起始地址还是0x40000000）. 然后cpu从0x00000000开始执行（也就是在Norfalsh中执行）。

### 04: 学习c函数的调用所带的实参和返回值在汇编中的实现
函数参数在汇编中会使用R0~R3寄存器进行传递，返回也通过R0~R3返回。
堆栈的用途：保存局部变量、保存寄存器

### 05: 在原先LED程序中添加关闭看门狗和自动选择NOR启动或NAND启动
在启动文件中关闭看门狗
通过向0地址写入数据看是否生效来确定是nor启动还是nand启动，会改变的是nand启动，因为代码运行会把nand flash中前4K数据存入SRAM中，否则是nor启动，这部分代码未经测试nor启动，因为openocd配置nor启动还不清楚。

### 06：使用头文件用按键控制LED
