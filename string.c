#include "shell.h"

/**
 * len_str - func that give me the length of string
 * @stri: string length
 *
 * Return: int length
 */
int len_str(char *stri)
{
	int x = 0;

	if (!stri)
		return (0);

	while (*stri++)
		x++;
	return (x);
}

/**
 * cmp_str - func that comparison of two strangs.
 * @st1: the first string
 * @st2: the second string
 *
 * Return: negative if st1 < st2, positive if st1 > st2, zero if st1 == st2
 */
int cmp_str(char *st1, char *st2)
{
	while (*st1 && *st2)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	if (*st1 == *st2)
		return (0);
	else
		return (*st1 < *st2 ? -1 : 1);
}

/**
 * push_hard - checks if fish starts with sea
 * @sea: string to search
 * @fish: the substring to find
 *
 * Return: address of next char of sea or NULL
 */
char *push_hard(const char *sea, const char *fish)
{
	while (*fish)
		if (*fish++ != *sea++)
			return (NULL);
	return ((char *)sea);
}

/**
 * cat_str - func that concatenates two strings
 * @track: buffer destination
 * @ori: buffer source
 *
 * Return: pointer to tracck buffer
 */
char *cat_str(char *track, char *ori)
{
	char *ret = track;

	while (*track)
		track++;
	while (*ori)
		*track++ = *ori++;
	*track = *ori;
	return (ret);
}
