#include "main.h"

/**
 * print_percent - Print a literal '%' character.
 *
 * This function prints a literal '%' character and does not process any
 * additional formatting options. It is used to print the '%' character as-is.
 *
 * @types: A va_list containing no relevant arguments.
 * @buffer: The buffer used for print operations.
 * @flags: Formatting flags.
 * @width: The desired width.
 * @precision: The precision specification.
 * @size: Size specifier.
 *
 * Return: The number of characters printed (always 1 for '%').
 */
int print_percent(va_list types, char buffer[],
				  int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_char - Prints a character.
 *
 * This function prints a single character based on the provided formatting
 * specifications. It handles optional formatting flags, width, and precision.
 *
 * @types: A va_list containing the character to be printed.
 * @buffer: The buffer used for printing.
 * @flags: Formatting flags.
 * @width: The desired width of the output.
 * @precision: The precision specification.
 * @size: Size specifier.
 *
 * Return: The number of characters printed (always 1 for characters).
 */
int print_char(va_list types, char buffer[],
			   int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 * print_string - Print a string with optional formatting.
 *
 * This function is responsible for printing a string, considering optional
 * formatting specifications such as flags, width, and precision. If no
 * string is provided, it handles "(null)" or space padding as needed.
 *
 * @types: A va_list containing the string to be printed.
 * @buffer: The buffer used for print operations.
 * @flags: Formatting flags for special handling.
 * @width: The desired width of the output.
 * @precision: The precision specification for the string (truncation).
 * @size: Size specifier.
 *
 * Return: The number of characters printed.
 */
int print_string(va_list types, char buffer[],
				 int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/**
 * print_binary - Print an unsigned integer in binary format.
 *
 * This function is responsible for printing an unsigned integer in
 * binary format.
 * It converts the integer into its binary representation and prints it to the
 * standard output. It does not process additional formatting options
 * like width or precision.
 *
 * @types: A va_list containing the unsigned integer to be printed in binary.
 * @buffer: The buffer used for print operations.
 * @flags: Formatting flags.
 * @width: The desired width of the output.
 * @precision: The precision specification.
 * @size: Size specifier for formatting.
 *
 * Return: The number of binary digits (0s and 1s) printed.
 */
int print_binary(va_list types, char buffer[],
				 int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

/**
 * print_int - Print an integer with optional formatting.
 *
 * This function is responsible for printing an integer, considering optional
 * formatting specifications such as flags, width, precision, and size. It
 * supports different size specifiers for integers and handles negative values.
 *
 * @types: A va_list containing the integer to be printed.
 * @buffer: The buffer used for print operations.
 * @flags: Formatting flags for special handling.
 * @width: The desired width of the output.
 * @precision: The precision specification for the integer.
 * @size: Size specifier for integers.
 *
 * Return: The number of characters printed.
 */
int print_int(va_list types, char buffer[],
			  int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

