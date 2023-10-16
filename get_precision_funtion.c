#include "main.h"

/**
 * get_precision - Extract the precision specification from a format string.
 *
 * This function is responsible for extracting and identifying the precision
 * specification from a format string. It checks for a period ('.') and parses
 * the precision value or retrieves it from the argument list using '*'.
 *
 * @format: The format string to parse, potentially containing a precision
 * specification.
 * @i: A pointer to the current position in the format string.
 * @list: A va_list of arguments for retrieving precision values from '*'.
 *
 * Return: The parsed precision value or -1 if not specified.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int current_i = *i + 1;
	int precision = -1;

	if (format[current_i] != '.')
		return (precision);

	precision = 0;

	for (current_i += 1; format[current_i] != '\0'; current_i++)
	{
		if (is_digit(format[current_i]))
		{
			precision *= 10;
			precision += format[current_i] - '0';
		}
		else if (format[current_i] == '*')
		{
			current_i++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = current_i - 1;

	return (precision);
}

