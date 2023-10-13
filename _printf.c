#include <stdarg.h>
#include <unistd.h>
#include "main.h"

/**
 * _printf - Custom printf function
 * @format: The format string
 *
 * Return: The number of characters printed
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    char buffer[1024];
    int i;

    va_start(args, format);

    while (format && *format)
    {
        if (*format == '%')
        {
            format++;
            if (*format == '\0')
                break;

            if (*format == 'c')
            {
                char c = va_arg(args, int);
                write(1, &c, 1);
                count++;
            }
            else if (*format == 's')
            {
                char *str = va_arg(args, char *);
                if (!str)
                    str = "(null)";
                while (*str)
                {
                    write(1, str, 1);
                    str++;
                    count++;
                }
            }
            else if (*format == '%')
            {
                write(1, "%", 1);
                count++;
            }
            else if (*format == 'd' || *format == 'i')
            {
                int num = va_arg(args, int);
                int len = 0;
                int temp = num;
                
		if (num < 0)
                {
                    write(1, "-", 1);
                    count++;
                    num = num * (-1);
                }
                if (num == 0)
                {
                    buffer[len++] = '0';
                }
                else
                {
                    while (temp != 0)
                    {
                        buffer[len++] = (temp % 10) + '0';
                        temp /= 10;
                    }
                }

		for (i = len - 1; i >= 0; i--)
                {
                    write(1, &buffer[i], 1);
                    count++;
                }
            }
            else if (*format == 'u')
            {
                unsigned int num = va_arg(args, unsigned int);
                int len = 0;
                unsigned int temp = num;

                if (num == 0)
                {
                    buffer[len++] = '0';
                }
                else
                {
                    while (temp != 0)
                    {
                        buffer[len++] = (temp % 10) + '0';
                        temp /= 10;
                    }
                }

                for (i = len - 1; i >= 0; i--)
                {
                    write(1, &buffer[i], 1);
                    count++;
                }
            }
            else if (*format == 'o')
            {
                unsigned int num = va_arg(args, unsigned int);
                int len = 0;
                unsigned int temp = num;

                if (num == 0)
                {
                    buffer[len++] = '0';
                }
                else
                {
                    while (temp != 0)
                    {
                        buffer[len++] = (temp % 8) + '0';
                        temp /= 8;
                    }
                }

                for (i = len - 1; i >= 0; i--)
                {
                    write(1, &buffer[i], 1);
                    count++;
                }
            }
            else if (*format == 'x' || *format == 'X')
            {
                unsigned int num = va_arg(args, unsigned int);
                int len = 0;
                unsigned int temp = num;

                if (num == 0)
                {
                    buffer[len++] = '0';
                }
                else
                {
                    char hexChars[] = "0123456789abcdef";
                    if (*format == 'X')
                    {
                        hexChars[10] = 'A';
                        hexChars[11] = 'B';
                        hexChars[12] = 'C';
                        hexChars[13] = 'D';
                        hexChars[14] = 'E';
                        hexChars[15] = 'F';
                    }
                    while (temp != 0)
                    {
                        buffer[len++] = hexChars[temp % 16];
                        temp /= 16;
                    }
                }

                for (i = len - 1; i >= 0; i--)
                {
                    write(1, &buffer[i], 1);
                    count++;
                }
            }
            else if (*format == 'p')
            {
                unsigned long address = (unsigned long)va_arg(args, void *);
                if (address == 0)
                {
                    write(1, "(nil)", 5);
                    count += 5;
                }
                else
                {
			int len = 0;
                    unsigned long temp = address;
                    write(1, "0x", 2);
                    count += 2;


                    if (address == 0)
                    {
                        buffer[len++] = '0';
                    }
                    else
                    {
                        char hexChars[] = "0123456789abcdef";
                        while (temp != 0)
                        {
                            buffer[len++] = hexChars[temp % 16];
                            temp /= 16;
                        }
                    }

                    for (i = len - 1; i >= 0; i--)
                    {
                        write(1, &buffer[i], 1);
                        count++;
                    }
                }
            }
            else
            {
                write(1, "%", 1);
                write(1, format, 1);
                count += 2;
            }
            format++;
        }
        else
        {
            write(1, format, 1);
            count++;
            format++;
        }
    }

    va_end(args);
    return count;
}
