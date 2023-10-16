#include "main.h"

/**
 * write_unsgnd - Write an unsigned number to a character buffer
 * with formatting.
 *
 * This function writes an unsigned number to the character buffer with the
 * specified formatting options, including width, precision, and padding.
 * It also considers whether the number is negative (0 for unsigned).
 *
 * @is_negative: A flag indicating whether the number is negative.
 * @ind: The current index in the buffer where writing starts.
 * @buffer: The character buffer to write the number to.
 * @flags: Formatting flags (e.g., F_MINUS for left-align).
 * @width: The total width of the output, including padding (if any).
 * @precision: The precision specification for the number.
 * @size: The size specifier for the number (e.g., S_LONG, S_SHORT).
 *
 * Return: The number of characters written to the buffer.
 */
int write_unsgnd(int is_negative, int ind,
				 char buffer[],
				 int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_number - Write a numeric value to a character buffer with formatting.
 *
 * This function handles writing a numeric value to the character buffer with
 * the specified formatting options, including width, precision, padding,
 * and extra characters like '+' or '-'.
 *
 * @is_negative: A flag indicating whether the number is negative.
 * @ind: The current index in the buffer where writing starts.
 * @buffer: The character buffer to write the numeric value to.
 * @flags: Formatting flags (e.g., F_MINUS for left-align).
 * @width: The total width of the output, including padding (if any).
 * @precision: The precision specification for the numeric value.
 * @size: The size specifier for the numeric value (e.g., S_LONG, S_SHORT).
 *
 * Return: The number of characters written to the buffer.
 */
int write_number(int is_negative, int ind, char buffer[],
				 int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
					  length, padd, extra_ch));
}

/**
 * handle_write_char - Write a character to a character buffer with formatting.
 *
 * This function handles writing a character to the character buffer with
 * the specified formatting options, including width, padding, and alignment.
 *
 * @c: The character to be written.
 * @buffer: The character buffer to write the character to.
 * @flags: Formatting flags (e.g., F_MINUS for left-align).
 * @width: The total width of the output, including padding (if any).
 * @precision: The precision specification for the character.
 * @size: Size specifier.
 *
 * Return: The number of characters written to the buffer.
 */
int handle_write_char(char c, char buffer[],
					  int flags, int width, int precision, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * write_num - Write a numeric value to a character buffer with formatting.
 *
 * This function writes a numeric value to the character buffer with the
 * specified formatting options, including width, precision, padding,
 * and extra characters.
 *
 * @ind: The current index in the buffer where writing starts.
 * @buffer: The character buffer to write the numeric value to.
 * @flags: Formatting flags (e.g., F_MINUS for left-align).
 * @width: The total width of the output, including padding (if any).
 * @prec: The precision specification for the numeric value.
 * @length: The length of the numeric value representation (including digits).
 * @padd: The padding character (' ' or '0').
 * @extra_c: An extra character to include (e.g., '+', ' ').
 *
 * Return: The number of characters written to the buffer.
 */
int write_num(int ind, char buffer[],
			  int flags, int width, int prec,
			  int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Write a pointer's hexadecimal representation
 * to a character buffer with formatting.
 *
 * This function writes a pointer's hexadecimal representation to the
 * character buffer with the specified formatting options, including width,
 * padding, extra characters, and alignment.
 *
 * @buffer: The character buffer to write the pointer representation to.
 * @ind: The current index in the buffer where writing starts.
 * @length: The length of the pointer representation.
 * @width: The total width of the output, including padding (if any).
 * @flags: Formatting flags (e.g., F_MINUS for left-align).
 * @padd: The padding character (' ' or '0').
 * @extra_c: An extra character to include (e.g., '+', ' ').
 * @padd_start: The starting index for padding (0 or 3 if '0x' is present).
 *
 * Return: The number of characters written to the buffer.
 */
int write_pointer(char buffer[], int ind, int length,
				  int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}

