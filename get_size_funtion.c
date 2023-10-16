#include "main.h"

/**
 * get_size - Extract size specifiers from a format string.
 *
 * This function is responsible for extracting and identifying size specifiers
 * from a format string. It checks for 'l' (long) or 'h' (short)
 * and returns corresponding size specifiers.
 * If no size specifier is found, it returns 0.
 *
 * @format: The format string to parse, potentially containing size specifiers.
 * @i: A pointer to the current position in the format string.
 *
 * Return: The size specifier found in the format string.
 */
int get_size(const char *format, int *i)
{
	int current_i = *i + 1;
	int size = 0;

	if (format[current_i] == 'l')
		size = S_LONG;
	else if (format[current_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = current_i - 1;
	else
		*i = current_i;

	return (size);
}

