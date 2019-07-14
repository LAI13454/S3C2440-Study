all:
	arm-none-eabi-gcc -c -o led.o led.c
	arm-none-eabi-gcc -c -o start.o start.S
	arm-none-eabi-ld -Ttext 0x0 -o led.elf start.o led.o
	arm-none-eabi-objcopy -O binary led.elf led.bin
	arm-none-eabi-objdump -S led.elf > led.dis
clean:
	rm *.o *.bin *.elf *.dis
