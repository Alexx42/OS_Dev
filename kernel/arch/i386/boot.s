
; Declare constants for the multiboot header
MBALIGN equ	1 << 0		; align loaded modules on page boundaries
MEMINFO equ	1 << 1		; provide memory map
VIDINFO equ	1 << 2
FLAGS	equ	MBALIGN | MEMINFO | VIDINFO		; multiboot 'flag' field
MAGIC	equ	0x1BADB002	; magic number
CHECKSUM	equ	-(MAGIC + FLAGS) ; checksum of above to prove we are MB

; Declare a multiboot header that marks the program as a kernel.

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
	dd VIDINFO

section .bss
align 16
stack_bottom:
resb 16384 ;16 KiB
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top	;esp register points to the top of the stack	 
	call _init
	extern	kernel_main
	call	kernel_main

	cli			; clear interrupt enable in eflags
.hang:	hlt			; wait for the next interrupt
	jmp .hang		; jump to the hlt instructions

.end:
