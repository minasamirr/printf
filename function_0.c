#include "main.h"

/**
 * print_octal - Print an unsigned integer in octal format.
 *
 * This function is responsible for printing an unsigned integer
 * in octal format.
 * It considers optional formatting specifications such as flags, width
 * and size specifiers. It also supports the '#' flag for prefixing octal
 * values with '0'.
 *
 * @types: A va_list containing the unsigned integer to be printed in octal
 * format.
 * @buffer: The buffer used for print operations.
 * @flags: Formatting flags for special handling.
 * @width: The desired width of the output.
 * @precision: The precision specification.
 * @size: Size specifier for unsigned integers.
 *
 * Return: The number of characters printed.
 */
int print_octal(va_list types, char buffer[],
				int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * print_hexa - Print an unsigned integer in hexadecimal format with custom
 * mapping.
 *
 * This function is responsible for printing an unsigned integer in hexadecimal
 * format, using a custom mapping for hexadecimal digits. It considers optional
 * formatting specifications such as flags, width, and size specifiers. It also
 * supports the '#' flag for prefixing the value with '0' and 'x' or 'X'.
 *
 * @types: A va_list containing the unsigned integer to be printed in
 * hexadecimal.
 * @map_to: A character array used to map hexadecimal digits.
 * @buffer: The buffer used for print operations.
 * @flags: Formatting flags for special handling.
 * @flag_ch: The character used to prefix the hexadecimal value.
 * @width: The desired width of the output.
 * @precision: The precision specification.
 * @size: Size specifier for unsigned integers.
 *
 * Return: The number of characters printed.
 */
int print_hexa(va_list types, char map_to[], char buffer[],
			   int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - Print an unsigned integer in hexadecimal format.
 *
 * This function is responsible for printing an unsigned integer in hexadecimal
 * format. It considers optional formatting specifications such as flags,
 * width, and size specifiers. It prints the integer in either lowercase ('x')
 * or uppercase ('X') hexadecimal format.
 *
 * @types: A va_list containing the unsigned integer to be printed in
 * hexadecimal.
 * @buffer: The buffer used for print operations.
 * @flags: Formatting flags for special handling.
 * @width: The desired width of the output.
 * @precision: The precision specification.
 * @size: Size specifier for unsigned integers.
 *
 * Return: The number of characters printed.
 */
int print_hexadecimal(va_list types, char buffer[],
					  int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
					   flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - Print an unsigned integer in uppercase hexadecimal
 * format.
 *
 * This function is responsible for printing an unsigned integer in uppercase
 * hexadecimal format. It considers optional formatting specifications such as
 * flags, width, and size specifiers. It prints the integer in uppercase ('X')
 * hexadecimal format.
 *
 * @types: A va_list containing the unsigned integer to be printed in uppercase
 *         hexadecimal format.
 * @buffer: The buffer used for print operations.
 * @flags: Formatting flags for special handling.
 * @width: The desired width of the output.
 * @precision: The precision specification.
 * @size: Size specifier for unsigned integers.
 *
 * Return: The number of characters printed.
 */
int print_hexa_upper(va_list types, char buffer[],
					 int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
					   flags, 'X', width, precision, size));
}

/**
 * print_unsigned - Print an unsigned integer with optional formatting.
 *
 * This function is responsible for printing an unsigned integer, considering
 * optional formatting specifications such as flags and width. It supports
 * different size specifiers for unsigned integers and does not handle
 * precision.
 *
 * @types: A va_list containing the unsigned integer to be printed.
 * @buffer: The buffer used for print operations.
 * @flags: Formatting flags for special handling.
 * @width: The desired width of the output.
 * @precision: The precision specification.
 * @size: Size specifier for unsigned integers.
 *
 * Return: The number of characters printed.
 */
int print_unsigned(va_list types, char buffer[],
				   int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
