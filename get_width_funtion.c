#include "main.h"

/**
 * get_width - Extract the width specification from a format string.
 *
 * This function is responsible for extracting and identifying the width specification
 * from a format string. It parses the width value if it's a positive integer or
 * retrieves it from the argument list using '*'.
 *
 * @format: The format string to parse, potentially containing a width specification.
 * @i: A pointer to the current position in the format string.
 * @list: A va_list of arguments for retrieving width values from '*'.
 *
 * Return: The parsed width value or 0 if not specified.
 */
int get_width(const char *format, int *i, va_list list)
{
	int current_i;
	int width = 0;

	for (current_i = *i + 1; format[current_i] != '\0'; current_i++)
	{
		if (is_digit(format[current_i]))
		{
			width *= 10;
			width += format[current_i] - '0';
		}
		else if (format[current_i] == '*')
		{
			current_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = current_i - 1;

	return (width);
}

