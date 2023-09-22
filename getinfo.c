#include "shell.h"

/**
 * clinformation - get info
 * @information: address
 */
void clinformation(info_t *information)
{
	information->arg = NULL;
	information->argv = NULL;
	information->path = NULL;
	information->argc = 0;
}

/**
 * s_information - initializes
 * @information: address
 * @argvec: vector
 */
void s_information(info_t *information, char **argvec)
{
	int ii = 0;

	information->fname = argvec[0];
	if (information->arg)
	{
		information->argv = split_str(information->arg, " \t");
		if (!information->argv)
		{

			information->argv = malloc(sizeof(char *) * 2);
			if (information->argv)
			{
				information->argv[0] = _strdup(information->arg);
				information->argv[1] = NULL;
			}
		}
		for (ii = 0; information->argv && information->argv[ii]; ii++)
			;
		information->argc = ii;

		replace_alias(information);
		replace_vars(information);
	}
}

/**
 * frinformation - free
 * @information: address
 * @al: true if free
 */
void frinformation(info_t *information, int al)
{
	ffree(information->argv);
	information->argv = NULL;
	information->path = NULL;
	if (al)
	{
		if (!information->cmd_buf)
			free(information->arg);
		if (information->env)
			release_lis(&(information->env));
		if (information->history)
			release_lis(&(information->history));
		if (information->alias)
			release_lis(&(information->alias));
		ffree(information->environ);
			information->environ = NULL;
		bfree((void **)information->cmd_buf);
		if (information->readfd > 2)
			close(information->readfd);
		_putchar(BUF_FLUSH);
	}
}
