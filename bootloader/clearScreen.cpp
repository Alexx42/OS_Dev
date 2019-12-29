void		clearScreen()
{
	__asm__ (
		"mov al, 02h" // here we set the 80x25 graphical mode (text)
		"mov ah, 00h" //allows us to change the video mode
		"int 10h" // call the interruption
	);
}
