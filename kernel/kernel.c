#include <stdio.h>
#include <kernel/tty.h>

void			kernel_main(
			void
			)
{
	/* Initialize the terminal interface */
	terminal_initialize();

	terminal_writestring("Hello, kernel World!\ntest");
}


















	
