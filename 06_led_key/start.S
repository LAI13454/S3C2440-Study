.text
.global _start

_start:
    /*
     * 关闭看门狗定时器
     */
    ldr r0, =0x53000000
    mov r1, #0
    str r1, [r0]

    /*
     * 通过写入0指针数据再读出，查看是否一致判断现在是nor启动还是nand启动，nand启动代码会被拷贝的SOC内部的4K RAM区
     * 可被读写，而nor不行
     */
    mov r0, #0
    ldr r1, [r0]
    str r0, [r0]
    ldr r2, [r0]
    cmp r0, r2
    ldr sp, =0x40000000 + 4096
    ldreq sp, =4096
    streq r1, [r0] 

    bl main
halt:
    b halt

