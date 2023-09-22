#include "shell.h"

/**
 * cpy_stri - copy string
 * @roa: the desti
 * @ori: the source
 *
 * Return: pointer to road
 */
char *cpy_stri(char *roa, char *ori)
{
	int i = 0;

	if (roa == ori || ori == 0)
		return (roa);
	while (ori[i])
	{
		roa[i] = ori[i];
		i++;
	}
	roa[i] = 0;
	return (roa);
}

/**
 * dupli_sat - duplicate string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *dupli_sat(const char *str)
{
	int len = 0;
	char *fit;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	fit = malloc(sizeof(char) * (len + 1));
	if (!fit)
		return (NULL);
	for (len++; len--;)
		fit[len] = *--str;
	return (fit);
}

/**
 *_puts - type input of string
 *@str: printed string
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _putchar - func that print char
 * @ch: The printed char
 *
 * Return: On success 1.
 * On error, -1 is returned
 */
int _putchar(char ch)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}
	if (ch != BUF_FLUSH)
		buf[x++] = ch;
	return (1);
}
