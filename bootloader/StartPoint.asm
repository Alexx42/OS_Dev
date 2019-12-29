bits 16
extern _BootMain:near

.code
.org 0x7c00h ; for BootSector
main:
	jmp short start ; go to main
	nop

start :
	cli
	mov ax, cs		; setup segment registers
	mov ds, ax		; make DS correct
	mov es, ax		; make ES correct
	mov ss, ax		; make SS correct
	mov bp,7c00h
	mov sp,7c00h		; setup stack
	sti

	call _BootMain
	ret
	END main
