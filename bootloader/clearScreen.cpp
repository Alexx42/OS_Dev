void		clearScreen()
{
	__asm__ (
		".intel_syntax\n"
		"mov %al, 02h"
		"mov %ah, 00h"
		"int 10h"
	);
}
