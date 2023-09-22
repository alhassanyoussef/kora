#include "shell.h"

/**
 * listlength - determines len
 * @hnode: pointer to first
 * Return: size
 */
size_t listlength(const list_t *hnode)
{
	size_t iii = 0;

	while (hnode)
	{
		hnode = hnode->next;
		iii++;
	}
	return (iii);
}

/**
 * listrings - returns array
 * @henode: pointer first
 * Return: array
 */
char **listrings(list_t *henode)
{
	list_t *n = henode;
	size_t iii = listlength(henode), jjj;
	char **strings;
	char *string;

	if (!henode || !iii)
		return (NULL);
	strings = malloc(sizeof(char *) * (iii + 1));
	if (!strings)
		return (NULL);
	for (iii = 0; n; n = n->next, iii++)
	{
		string = malloc(len_str(n->str) + 1);
		if (!string)
		{
			for (jjj = 0; jjj < iii; jjj++)
				free(strings[jjj]);
			free(strings);
			return (NULL);
		}

		string = _strcpy(string, n->str);
		strings[iii] = string;
	}
	strings[iii] = NULL;
	return (strings);
}


/**
 * pri_li - prints
 * @hh: first node
 * Return: list size
 */
size_t pri_li(const list_t *hh)
{
	size_t iii = 0;

	while (hh)
	{
		_puts(convnum(hh->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hh->str ? hh->str : "(nil)");
		_puts("\n");
		hh = hh->next;
		iii++;
	}
	return (iii);
}

/**
 * n_start - returns node
 * @n: list head
 * @fix: string
 * @cc: next character
 * Return: node or null
 */
list_t *n_start(list_t *n, char *fix, char cc)
{
	char *pp = NULL;

	while (n)
	{
		pp = push_hard(n->str, fix);
		if (pp && ((cc == -1) || (*pp == cc)))
			return (n);
		n = n->next;
	}
	return (NULL);
}

/**
 * gt_index - index of a node
 * @h: list head
 * @n: node
 * Return: node or -1
 */
ssize_t gt_index(list_t *h, list_t *n)
{
	size_t iii = 0;

	while (h)
	{
		if (h == n)
			return (iii);
		h = h->next;
		iii++;
	}
	return (-1);
}
