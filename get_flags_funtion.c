#include "main.h"

/**
 * get_flags - Extract formatting flags from a format string.
 *
 * This function is responsible for extracting and identifying formatting flags
 * from a format string. It supports the flags '-', '+', '0', '#', and ' ' and
 * returns a corresponding bitmask based on the encountered flags.
 *
 * @format: The format string to parse, containing formatting flags.
 * @i: A pointer to the current position in the format string.
 *
 * Return: A bitmask representing the formatting flags encountered.
 */
int get_flags(const char *format, int *i)
{
	int j, current_i;
	int flags = 0;
	const char FLAG_CHAR[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAG_ARRAY[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (current_i = *i + 1; format[current_i] != '\0'; current_i++)
	{
		for (j = 0; FLAG_CHAR[j] != '\0'; j++)
			if (format[current_i] == FLAG_CHAR[j])
			{
				flags |= FLAG_ARRAY[j];
				break;
			}

		if (FLAG_CHAR[j] == 0)
			break;
	}

	*i = current_i - 1;

	return (flags);
}

