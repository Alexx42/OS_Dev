#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "You are not using a cross-compiler"
#endif

#if !defined(__i386__)
#error "Needs to be compiled with a ix86-elf compiler"
#endif

// Hardware text mode color constants
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15
};

static inline uint8_t	vga_entry_color(
			enum vga_color fg,
			enum vga_color bg
			)
{
	return fg | bg << 4;
}

static inline uint16_t	vga_entry(
			unsigned char uc,
			uint8_t color
			)
{
	return (uint16_t)uc | (uint16_t)color << 8;
}

size_t			strlen(
			const char *str
			)
{
	size_t len;

	len = 0;
	while (str[len])
		len++;
	return len;
}

static const size_t	VGA_WIDTH	= 80;
static const size_t	VGA_HEIGHT	= 25;

size_t			terminal_row;
size_t			terminal_column;
uint8_t			terminal_color;
uint16_t		*terminal_buffer;


void			terminal_initialize(
			void
			)
{
	size_t		y;
	size_t		x;
	size_t		index;

	y = 0;
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t *)0xB8000;
	while (y < VGA_HEIGHT) {
		x = 0;
		while (x < VGA_WIDTH) {
			index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
			x++;
		}
		y++;
	}
}

void			terminal_setcolor(
			uint8_t color
			)
{
	terminal_color = color;
}

void			terminal_putentryat(
			char		c,
			uint8_t		color,
			size_t 		x,
			size_t		y
			)
{
	size_t		index;

	index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}


void			terminal_putchar(
			char c
			)
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
	if (c == '\n') {
		terminal_row++;
		terminal_column = 0;
	}
}

void			terminal_write(
			const char	*data,
			size_t		size
			)
{
	size_t		i;

	i = 0;
	while (i < size) {
		terminal_putchar(data[i]);
		i++;
	}
}

void			terminal_writestring(
			const char *data
			)
{
	terminal_write(data, strlen(data));
}

void			kernel_main(
			void
			)
{
	/* Initialize the terminal interface */
	terminal_initialize();

	terminal_writestring("Hello, kernel World!\ntest");
}


















	