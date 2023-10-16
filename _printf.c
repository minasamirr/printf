#include "main.h"

/**
 * print_buffer - Prints the contents of a character buffer, if it exists.
 *
 * This function is responsible for printing the contents of the character
 * buffer to the standard output (typically the console). If the buffer
 * contains data, it is printed, and the buffer index (length)
 * is reset to zero.
 *
 * @buffer: The character array containing the data to be printed.
 * @buff_ind: A pointer to an integer indicating
 * the current buffer index/length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

/**
 * _printf - Custom printf function
 *
 * This function provides a custom implementation of the printf function
 * for formatted output. It processes the format string and its optional
 * format specifiers, allowing for customized printing of various data types
 * and text. The function supports standard format specifiers and provides
 * options for width, precision, and flags to control formatting.
 *
 * @format: The format string that contains the text and format specifiers.
 *
 * Return: The total number of characters printed to the standard output.
 *         Returns -1 on error.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
								   flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);
	va_end(list);

	return (printed_chars);
}

