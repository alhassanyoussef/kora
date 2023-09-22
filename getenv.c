#include "shell.h"

/**
 * catch_env - func that return str array copy of our env
 * @in_fo: struct contain prop args, used for save function
 * Return: Always 0
 */
char **catch_env(info_t *in_fo)
{
	if (!in_fo->environ || in_fo->env_changed)
	{
		in_fo->environ = listrings(in_fo->env);
		in_fo->env_changed = 0;
	}

	return (in_fo->environ);
}

/**
 * jax_str - delete an environment cha
 * @in_fo: struct contain prop args, used for save function
 *  Return: 1 on delete, 0 otherwise
 * @cha: the str env cha prop
 */
int jax_str(info_t *in_fo, char *cha)
{
	list_t *cream = in_fo->env;
	size_t x = 0;
	char *pt;

	if (!cream || !cha)
		return (0);

	while (cream)
	{
		pt = push_hard(cream->str, cha);
		if (pt && *pt == '=')
		{
			in_fo->env_changed = del_nody_atindex(&(in_fo->env), x);
			x = 0;
			cream = in_fo->env;
			continue;
		}
		cream = cream->next;
		x++;
	}
	return (in_fo->env_changed);
}

/**
 * seraphine_str - create a new en_v varia,
 *             or edit an existing one
 * @in_fo: struct contain prop args, used for save function
 * @cha: the string env cha property
 * @cap: the str env cha cap
 *  Return: Always 0
 */
int seraphine_str(info_t *in_fo, char *cha, char *cap)
{
	char *vanilla = NULL;
	list_t *cream;
	char *p;

	if (!cha || !cap)
		return (0);

	vanilla = malloc(len_str(cha) + len_str(cap) + 2);
	if (!vanilla)
		return (1);
	cpy_stri(vanilla, cha);
	cat_str(vanilla, "=");
	cat_str(vanilla, cap);
	cream = in_fo->env;
	while (cream)
	{
		p = push_hard(cream->str, cha);
		if (p && *p == '=')
		{
			free(cream->str);
			cream->str = vanilla;
			in_fo->env_changed = 1;
			return (0);
		}
		cream = cream->next;
	}
	add_nody_end(&(in_fo->env), vanilla, 0);
	free(vanilla);
	in_fo->env_changed = 1;
	return (0);
}
