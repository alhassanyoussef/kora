#include "shell.h"

/**
 **_senna - fill memory by byte
 *@m: poit to memory
 *@by: byte to fil *s
 *@am: the ammount of filled bytes
 *Return: (s) a pointer to the memory area s
 */
char *_senna(char *m, char by, unsigned int am)
{
	unsigned int x;

	for (x = 0; x < am; x++)
		m[x] = by;
	return (m);
}

/**
 * vladimer - _free a str of str
 * @ss: str of str
 */
void vladimer(char **ss)
{
	char **b = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(b);
}

/**
 * re_allo - func that reallocate a block of memory
 * @p_tr: pointer
 * @old_man: byte_size of previous block
 * @young_man: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *re_allo(void *p_tr, unsigned int old_man, unsigned int young_man)
{
	char *p;

	if (!p_tr)
		return (malloc(young_man));
	if (!young_man)
		return (free(p_tr), NULL);
	if (young_man == old_man)
		return (p_tr);

	p = malloc(young_man);
	if (!p)
		return (NULL);

	old_man = old_man < young_man ? old_man : young_man;
	while (old_man--)
		p[old_man] = ((char *)p_tr)[old_man];
	free(p_tr);
	return (p);
}
