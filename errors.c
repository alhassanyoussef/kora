#include "shell.h"

/**
 *print_str - func that input str
 * @str: printed str
 *
 * Return: Nothing
 */
void print_str(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		write_char(str[x]);
		x++;
	}
}

/**
 * write_char - write the  char to stderr
 * @ch: The printed char
 *
 * Return: success 1.
 * On error, -1 is returned, and errno is set appro.
 */
int write_char(char ch)
{
	static int y;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || y >= WRITE_BUF_SIZE)
	{
		write(2, buf, y);
		y = 0;
	}
	if (ch != BUF_FLUSH)
		buf[y++] = ch;
	return (1);
}

/**
 * write_fd - write char c to fde
 * @ch: printed char
 * @fde: The filed_escriptor to write to
 *
 * Return: success 1.
 * On error, -1 is returned, and errno is set approp.
 */
int write_fd(char ch, int fde)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(fde, buf, m);
		m = 0;
	}
	if (ch != BUF_FLUSH)
		buf[m++] = ch;
	return (1);
}

/**
 *puts_fde - func that print an input string
 * @st: the printed str
 * @fde: the filed_escriptor to write to
 *
 * Return: the number of chars put
 */
int puts_fde(char *st, int fde)
{
	int w = 0;

	if (!st)
		return (0);
	while (*st)
	{
		w += write_fd(*st++, fde);
	}
	return (w);
}
