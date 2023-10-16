#include "main.h"

/**
 * print_non_printable - Print a string with non-printable characters as
 * hexadecimal codes.
 *
 * This function is responsible for printing a string, replacing non-printable
 * characters with their hexadecimal codes.
 * It considers optional formatting
 * specifications such as flags, width, and size specifiers but does not
 * process them. The function scans the input string for non-printable
 * characters and replaces them with their hexadecimal codes.
 *
 * @types: A va_list containing the string to be printed with non-printable
 * characters replaced.
 * @buffer: The buffer used for print operations.
 * @flags: Formatting flags.
 * @width: The desired width of the output.
 * @precision: The precision specification.
 * @size: Size specifier for formatting.
 *
 * Return: The number of characters printed, including hexadecimal codes.
 */
int print_non_printable(va_list types, char buffer[],
						int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/**
 * print_pointer - Print a pointer address in hexadecimal format.
 *
 * This function is responsible for printing a pointer address in hexadecimal
 * format.
 * It considers optional formatting specifications such as flags, width,
 * and size specifiers. The function also supports zero-padding and the
 * addition of a plus sign or space before the address.
 *
 * @types: A va_list containing the pointer address to be printed.
 * @buffer: The buffer used for print operations.
 * @flags: Formatting flags (e.g., zero-padding, plus sign).
 * @width: The desired width of the output.
 * @precision: The precision specification.
 * @size: Size specifier for formatting.
 *
 * Return: The number of characters printed for the pointer address.
 */
int print_pointer(va_list types, char buffer[],
				  int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1;
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
						  width, flags, padd, extra_c, padd_start));
}

/**
 * print_rot13string - Print a string using the ROT13 cipher.
 *
 * This function is responsible for printing a string using the ROT13 cipher.
 * It considers optional formatting specifications such as flags, width
 * and size specifiers but does not process them. It transforms the input
 * string using the ROT13 cipher and prints the result to the standard output.
 *
 * @types: A va_list containing the string to be transformed and printed
 * using ROT13.
 * @buffer: The buffer used for print operations.
 * @flags: Formatting flags.
 * @width: The desired width of the output.
 * @precision: The precision specification.
 * @size: Size specifier for formatting.
 *
 * Return: The number of characters printed after ROT13 transformation.
 */
int print_rot13string(va_list types, char buffer[],
					  int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}

/**
 * print_reverse - Print a string in reverse order.
 *
 * This function is responsible for printing a string in reverse order. It
 * considers optional formatting specifications such as flags, width, and size
 * specifiers but does not process them. The function reverses the input string
 * and prints the reversed string to the standard output.
 *
 * @types: A va_list containing the string to be reversed and printed.
 * @buffer: The buffer used for print operations.
 * @flags: Formatting flags.
 * @width: The desired width of the output.
 * @precision: The precision specification.
 * @size: Size specifier for formatting.
 *
 * Return: The number of characters printed in reverse order.
 */

int print_reverse(va_list types, char buffer[],
				  int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
