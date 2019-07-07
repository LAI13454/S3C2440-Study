all:
    arm-none-eabi-gcc -c -o led_on.o led_on.S
    arm-none-eabi-ld -Ttext 0x0 -o led_on.elf led_on.o
    arm-none-eabi-objcopy -O binary led_on.elf led_on.bin
    arm-none-eabi-dum    
