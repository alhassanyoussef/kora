#include "shell.h"

/**
 * err - converts
 * @ss: the string
 * Return: 0 if no num,otherwise -1 on error
 */
int err(char *ss)
{
	int ii = 0;
	unsigned long int res = 0;

	if (*ss == '+')
		ss++;
	for (ii = 0;  ss[ii] != '\0'; ii++)
	{
		if (ss[ii] >= '0' && ss[ii] <= '9')
		{
			res *= 10;
			res += (ss[ii] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * printerr - prints
 * @information: the param
 * @estring: string
 * Return: 0 if no num,otherwise -1 on error
 */
void printerr(info_t *information, char *estring)
{
	print_str(information->fname);
	print_str(": ");
	printdec(information->line_count, STDERR_FILENO);
	print_str(": ");
	print_str(information->argv[0]);
	print_str(": ");
	print_str(estring);
}

/**
 * printdec - prints
 * @in: the in
 * @filed: the file
 * Return: number
 */
int printdec(int in, int filed)
{
	int (*__putchar)(char) = write_char;
	int ii, counter = 0;
	unsigned int abs, curr;

	if (filed == STDERR_FILENO)
		__putchar = write_char;
	if (in < 0)
	{
		abs = -in;
		__putchar('-');
		counter++;
	}
	else
		abs = in;
	curr = abs;
	for (ii = 1000000000; ii > 1; ii /= 10)
	{
		if (abs / ii)
		{
			__putchar('0' + curr / ii);
			counter++;
		}
		curr %= ii;
	}
	__putchar('0' + curr);
	counter++;

	return (counter);
}

/**
 * convnum - converter
 * @number: number
 * @bas: baase
 * @fla: flags
 *
 * Return: string
 */
char *convnum(long int number, int bas, int fla)
{
	static char *arr;
	static char buf[50];
	char s = 0;
	char *p;
	unsigned long nn = number;

	if (!(fla & CONVERT_UNSIGNED) && number < 0)
	{
		nn = -number;
		s = '-';

	}
	arr = fla & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buf[49];
	*p = '\0';

	do	{
		*--p = arr[nn % bas];
		nn /= bas;
	} while (nn != 0);

	if (s)
		*--p = s;
	return (p);
}

/**
 * remcomm - function replaces
 * @buff: address
 * Return: Always 0;
 */
void remcomm(char *buff)
{
	int ii;

	for (ii = 0; buff[ii] != '\0'; ii++)
		if (buff[ii] == '#' && (!ii || buff[ii - 1] == ' '))
		{
			buff[ii] = '\0';
			break;
		}
}
