/*
 * 点亮LED
 */

.text
.global _start

_start:

/*
 * 配置GPF5设置为输出模式
 */
	ldr r0, =0x56000050
	ldr r1, =0x1000
	str r1, [r0]

/*
 * 配置GPF5输出低电平，点亮LED
 */
	ldr r0, =0x56000054
	ldr r1, =0x0
	str r1, [r0]


halt:
	b halt

	
