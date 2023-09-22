#include "shell.h"

/**
 * fr - frees
 * @pointr: address to free
 * Return: 1 free, otherwise 0.
 */
int fr(void **pointr)
{
	if (pointr && *pointr)
	{
		free(*pointr);
		*pointr = NULL;
		return (1);
	}
	return (0);
}
