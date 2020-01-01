section .init
global _init:function()
_init:
	push ebp
	movl ebp, esp

section .fini
global _fini:function()
_fini:
	push ebp
	movl ebp, esp
