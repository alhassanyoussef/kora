#include "shell.h"

/**
 * my_date - func that show history list
 * @info: Structure contain potential arg. Used to maintain
 *        cons function prototype.
 *  Return: Always 0
 */
int my_date(info_t *info)
{
	pri_li(info->history);
	return (0);
}

/**
 * uncont_alias - sets ali to str
 * @info: parameter struct
 * @str: the string ali
 *
 * Return: Always 0 on success, 1 on error
 */
int uncont_alias(info_t *info, char *str)
{
	char *a, b;
	int vex;

	a = char_str(str, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	vex = del_nody_atindex(&(info->alias),
		gt_index(info->alias, n_start(info->alias, str, -1)));
	*a = b;
	return (vex);
}

/**
 * cont_ali - sets ali to string
 * @info: factor struct
 * @str: the str ali
 *
 * Return: Always 0 on success, 1 on error
 */
int cont_ali(info_t *info, char *str)
{
	char *x;

	x = char_str(str, '=');
	if (!x)
		return (1);
	if (!*++x)
		return (uncont_alias(info, str));

	uncont_alias(info, str);
	return (add_nody_end(&(info->alias), str, 0) == NULL);
}

/**
 * impri_alias - print an ali str
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int impri_alias(list_t *node)
{
	char *x = NULL, *y = NULL;

	if (node)
	{
		x = char_str(node->str, '=');
		for (y = node->str; y <= x; y++)
			_putchar(*y);
		_putchar('\'');
		_puts(x + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_mine - mimi the ali builtin
 * @info: Struct contain poten arg. Used to maintain
 *          cons func proto.
 *  Return: Always 0
 */
int alias_mine(info_t *info)
{
	int j = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			impri_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		p = char_str(info->argv[j], '=');
		if (p)
			cont_ali(info, info->argv[j]);
		else
			impri_alias(n_start(info->alias, info->argv[j], '='));
	}

	return (0);
}
