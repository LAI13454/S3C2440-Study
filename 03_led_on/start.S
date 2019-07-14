.text
.global _start

_start:
    ldr sp, =4096
    
    bl main
halt:
    b halt

