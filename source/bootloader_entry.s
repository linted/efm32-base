.section .text_bootloader

.align 4
.global __Vectors
.global Reset_Handler

__Vectors:
.word Reset_Handler
.word 0
.word 0

Reset_Handler:
    b Reset_Handler
