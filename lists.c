#include "shell.h"

/**
 * insert_node - inserts a node at the beginning of the list
 * @headd: pointer to the head node
 * @str: string field of the node
 * @num: node index used for history
 *
 * Return: size of the list
 */

list_t *insert_node(list_t **headd, const char *str, int num)
{
	list_t *new_headd;

	if (!headd)
		return (NULL);
	new_headd = malloc(sizeof(list_t));
	if (!new_headd)
		return (NULL);
	_memset((void *)new_headd, 0, sizeof(list_t));
	new_headd->num = num;
	if (str)
	{
		new_headd->str = _strdup(str);
		if (!new_headd->str)
		{
			free(new_headd);
			return (NULL);
		}
	}
	new_headd->next = *headd;
	*headd = new_headd;
	return (new_headd);
}

/**
 * add_nody_end - inserts a node at the end of the list
 * @headd: pointer to the head node
 * @str: string field of the node
 * @num: node index used for history
 *
 * Return: size of the list
 */

list_t *add_nody_end(list_t **headd, const char *str, int num)
{
	list_t *new_nody, *node;

	if (!headd)
		return (NULL);

	node = *headd;
	new_nody = malloc(sizeof(list_t));
	if (!new_nody)
		return (NULL);
	_memset((void *)new_nody, 0, sizeof(list_t));
	new_nody->num = num;
	if (str)
	{
		new_nody->str = _strdup(str);
		if (!new_nody->str)
		{
			free(new_nody);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_nody;
	}
	else
		*headd = new_nody;
	return (new_nody);
}

/**
 * type_strlist - prints only the string field of a list_t linked list
 * @s: pointer to the first node
 *
 * Return: size of the list
 */
size_t type_strlist(const list_t *s)
{
	size_t y = 0;

	while (s)
	{
		_puts(s->str ? s->str : "(nil)");
		_puts("\n");
		s = s->next;
		y++;
	}
	return (y);
}

/**
 * del_nody_atindex - remove node at a certain index
 * @headd: pointer address to the first node
 * @ind: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int del_nody_atindex(list_t **headd, unsigned int ind)
{
	list_t *nody, *prev_nody;
	unsigned int x = 0;

	if (!headd || !*headd)
		return (0);

	if (!ind)
	{
		nody = *headd;
		*headd = (*headd)->next;
		free(nody->str);
		free(nody);
		return (1);
	}
	nody = *headd;
	while (nody)
	{
		if (x == ind)
		{
			prev_nody->next = nody->next;
			free(nody->str);
			free(nody);
			return (1);
		}
		x++;
		prev_nody = nody;
		nody = nody->next;
	}
	return (0);
}

/**
 * release_lis - frees all nodes of a list
 * @headd_p: address of pointer to headd node
 *
 * Return: void
 */
void release_lis(list_t **headd_p)
{
	list_t *nody, *next_nody, *headd;

	if (!headd_p || !*headd_p)
		return;
	headd = *headd_p;
	nody = headd;
	while (nody)
	{
		next_nody = nody->next;
		free(nody->str);
		free(nody);
		nody = next_nody;
	}
	*headd_p = NULL;
}
