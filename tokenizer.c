#include "shell.h"

/**
 * **split_str - devides string into words
 * @str: string input
 * @de: string delimeter
 * Return: pointer
 */

char **split_str(char *str, char *de)
{
	int w, x, y, z, num_words = 0;
	char **so;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!de)
		de = " ";
	for (w = 0; str[w] != '\0'; w++)
		if (!is_that_deli(str[w], d) &&
			(is_that_deli(str[w + 1], de) || !str[w + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	so = malloc((1 + num_words) * sizeof(char *));
	if (!so)
		return (NULL);
	for (w = 0, x = 0; x < num_words; x++)
	{
		while (is_that_deli(str[i], de))
			w++;
		y = 0;
		while (!is_that_deli(str[w + y], de) && str[w + y])
			y++;
		so[x] = malloc((y + 1) * sizeof(char));
		if (!so[x])
		{
			for (y = 0; y < x; y++)
				free(so[y]);
			free(so);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			so[x][z] = str[w++];
		so[x][z] = 0;
	}
	so[x] = NULL;
	return (so);
}

/**
 * **split_str2 - divide a string into words
 * @str: string input
 * @de: deli
 * Return: a pointer to an array of str, or NULL on fail
 */
char **split_str2(char *str, char de)
{
	int x, z, k, m, new_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != de && str[x + 1] == de) ||
		    (str[x] != de && !str[x + 1]) || str[x + 1] == de)
			new_words++;
	if (new_words == 0)
		return (NULL);
	s = malloc((1 + new_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, z = 0; z < new_words; z++)
	{
		while (str[x] == de && str[x] != de)
			x++;
		k = 0;
		while (str[x + k] != de && str[x + k] && str[x + k] != de)
			k++;
		s[z] = malloc((k + 1) * sizeof(char));
		if (!s[z])
		{
			for (k = 0; k < z; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[z][m] = str[x++];
		s[z][m] = 0;
	}
	s[z] = NULL;
	return (s);
}
