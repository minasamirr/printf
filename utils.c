#include "main.h"

/**
 * is_digit - Check if a character is a digit.
 *
 * This function determines whether a given character is a digit (0-9).
 *
 * @c: The character to check.
 *
 * Return: 1 if the character is a digit, 0 otherwise.
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * is_printable - Check if a character is a printable ASCII character.
 *
 * This function determines whether a given character is a printable ASCII
 * character, falling within the range of ASCII values 32 to 126,
 * which includes visible and readable characters.
 *
 * @c: The character to check.
 *
 * Return: 1 if the character is a printable ASCII character, 0 otherwise.
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * convert_size_number - Convert a long integer to a specific data type.
 *
 * This function is responsible for converting a long integer to a specific
 * data type based on the provided size specifier.
 * It ensures compatibility with different size
 * specifiers, such as long or short, by casting the value accordingly.
 *
 * @num: The long integer to convert.
 * @size: The size specifier for the target data type.
 *
 * Return: The converted value of the long integer to the specified data type.
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Convert an unsigned long integer to
 * a specific data type.
 *
 * This function is responsible for converting an unsigned long integer
 * to a specific data type based on the provided size specifier.
 * It ensures compatibility with different size specifiers,
 * such as long or short, by casting the value accordingly.
 *
 * @num: The unsigned long integer to convert.
 * @size: The size specifier for the target data type.
 *
 * Return: The converted value of the unsigned long integer to
 * the specified data type.
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}

/**
 * append_hexa_code - Append a hexadecimal representation of an ASCII
 * character code to a buffer.
 *
 * This function appends a hexadecimal representation of the given
 * ASCII character code to the provided character buffer in the format "\xXX,"
 * where 'XX' are two hexadecimal digits.
 *
 * @ascii_code: The ASCII character code to convert to hexadecimal.
 * @buffer: The character buffer to which the hexadecimal
 * code is appended.
 * @i: The current index in the buffer where the hexadecimal
 * code should be added.
 *
 * Return: The number of characters appended to the buffer.
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}
