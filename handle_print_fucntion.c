#include "main.h"

/**
 * handle_print - Handle and dispatch printing based on format specifiers.
 *
 * This function is responsible for handling and dispatching printing based
 * on format specifiers encountered in the format string.
 * It supports a variety of format specifiers, including characters, strings,
 * integers, and more, each represented by a character.
 * The function calls the corresponding print function based on the format
 * specifier and delegates the printing operation. If an unknown specifier is
 * encountered, it prints the specifier character as a literal character and
 * handles any associated formatting options.
 *
 * @fmt: The format string to parse, containing format specifiers and
 * optional formatting options.
 * @ind: A pointer to the current position in the format string.
 * @list: A va_list of arguments for printing.
 * @buffer: The buffer used for print operations.
 * @flags: Formatting flags.
 * @width: The desired width of the output.
 * @precision: The precision specification.
 * @size: Size specifier for formatting.
 *
 * Return: The number of characters printed by the selected print function
 * or -1 if an unknown specifier is encountered.
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
				 int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string},
		{'%', print_percent}, {'i', print_int},
		{'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal},
		{'x', print_hexadecimal}, {'X', print_hexa_upper},
		{'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string},
		{'\0', NULL}};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}

