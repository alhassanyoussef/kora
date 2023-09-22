#include "shell.h"

/**
 * inter_act - returns one if shell is inter_act mode
 * @info: struct add
 *
 * Return: 1 if inter_act mode, 0 otherwise
 */
int inter_act(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_that_deli - examine if char is a delieter
 * @le: the char to examine
 * @deli: the deli string
 * Return: 1 if true, 0 if false
 */
int is_that_deli(char le, char *deli)
{
	while (*deli)
		if (*deli++ == le)
			return (1);
	return (0);
}

/**
 *is_alpha - examine for alphapet char
 *@le: The char to input
 *Return: 1 if le is alphapet, 0 otherwise
 */

int is_alpha(int le)
{
	if ((le >= 'a' && le <= 'z') || (le >= 'A' && le <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *a_toi - turn a string to an integer
 *@s: the str to be turned
 *Return: 0 if no num in str, converted num otherwise
 */

int a_toi(char *s)
{
	int x, sign = 1, flagg = 0, output;
	unsigned int outcome = 0;

	for (x = 0;  s[x] != '\0' && flagg != 2; x++)
	{
		if (s[x] == '-')
			sign *= -1;

		if (s[x] >= '0' && s[x] <= '9')
		{
			flagg = 1;
			outcome *= 10;
			outcome += (s[x] - '0');
		}
		else if (flagg == 1)
			flagg = 2;
	}

	if (sign == -1)
		output = -outcome;
	else
		output = outcome;

	return (output);
}
