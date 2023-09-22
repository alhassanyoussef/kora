#include "shell.h"

/**
 **copy_string - copies a string
 *@desti: the destiination string to be copied to
 *@sor: the source string
 *@nu: the amount of characters to be copied
 *Return: the concatenated string
 */
char *copy_string(char *desti, char *sor, int nu)
{
	int x, y;
	char *s = desti;

	x = 0;
	while (sor[x] != '\0' && x < nu - 1)
	{
		desti[x] = sor[x];
		x++;
	}
	if (x < nu)
	{
		y = x;
		while (y < nu)
		{
			desti[y] = '\0';
			y++;
		}
	}
	return (s);
}

/**
 **concat_str - concat two str
 *@desti: the 1th string
 *@sor: the 2st string
 *@nu: the amount of bytes
 *Return: the concatenated string
 */
char *concat_str(char *desti, char *sor, int nu)
{
	int x, y;
	char *s = desti;

	x = 0;
	y = 0;
	while (desti[x] != '\0')
		x++;
	while (sor[y] != '\0' && y < nu)
	{
		desti[x] = sor[y];
		x++;
		y++;
	}
	if (y < nu)
		desti[x] = '\0';
	return (s);
}

/**
 **char_str - locates a char in a str
 *@st: the str to be parsed
 *@ch: the char to look for
 *Return: (s) a pointer to the memory area s
 */
char *char_str(char *st, char ch)
{
	do {
		if (*st == ch)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}
