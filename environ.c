#include "shell.h"

/**
 * my_enviro - prints environment
 * @information: Used to maintain
 * Return: Always 0
 */
int my_enviro(info_t *information)
{
	type_strlist(information->env);
	return (0);
}

/**
 * get_enviro - gets environ variables
 * @information: Used to maintain
 * @get_name: get enviroment name
 * Return: value
 */
char *get_enviro(info_t *information, const char *get_name)
{
	list_t *n = information->env;
	char *pp;

	while (n)
	{
		pp = push_hard(n->str, get_name);
		if (pp && *pp)
			return (pp);
		n = n->next;
	}
	return (NULL);
}

/**
 * my_set_env - set a new environment variable
 * @information: Used to maintain
 *  Return: Always 0
 */
int my_set_env(info_t *information)
{
	if (information->argc != 3)
	{
		print_str("Incorrect number of arguements\n");
		return (1);
	}
	if (seraphine_str(information, information->argv[1], information->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unset_env - Removes environment
 * @information: Used to maintain
 *  Return: Always 0
 */
int my_unset_env(info_t *information)
{
	int ii;

	if (information->argc == 1)
	{
		print_str("Too few arguements.\n");
		return (1);
	}
	for (ii = 1; ii <= information->argc; ii++)
		jax_str(information, information->argv[ii]);

	return (0);
}

/**
 * pop_envlist - populates env
 * @information: Used to maintaine
 * Return: Always 0
 */
int pop_envlist(info_t *information)
{
	list_t *n = NULL;
	size_t ii;

	for (ii = 0; environ[ii]; ii++)
		add_nody_end(&n, environ[ii], 0);
	information->env = n;
	return (0);
}

