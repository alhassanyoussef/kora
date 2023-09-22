#include "shell.h"

/**
 * chain - tests
 * @inf: the parameter
 * @buffe: buffer
 * @posi: address position
 * Return: 1 delimeter, 0 otherwise
 */
int chain(info_t *inf, char *buffe, size_t *posi)
{
	size_t jj = *posi;

	if (buffe[jj] == '|' && buffe[jj + 1] == '|')
	{
		buffe[jj] = 0;
		jj++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buffe[jj] == '&' && buffe[jj + 1] == '&')
	{
		buffe[jj] = 0;
		jj++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buffe[jj] == ';')
	{
		buffe[jj] = 0;
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*posi = jj;
	return (1);
}

/**
 * ch_ch - checks chaining
 * @inf: struct
 * @buffe: buffer
 * @posi: address position
 * @star: starting position
 * @length: length buffe
 * Return:
 */
void ch_ch(info_t *inf, char *buffe, size_t *posi, size_t star, size_t length)
{
	size_t jj = *posi;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buffe[star] = 0;
			jj = length;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buffe[star] = 0;
			jj = length;
		}
	}

	*posi = jj;
}

/**
 * rep_ali - replaces
 * @inf: struct
 * Return: 1 or 0 otherwise
 */
int rep_ali(info_t *inf)
{
	int iii;
	list_t *n;
	char *posi;

	for (iii = 0; iii < 10; iii++)
	{
		n = n_start(inf->alias, inf->argv[0], '=');
		if (!n)
			return (0);
		free(inf->argv[0]);
		posi = char_str(n->str, '=');
		if (!posi)
			return (0);
		posi = dupli_sat(posi + 1);
		if (!posi)
		posi = dupli_sat(posi + 1);
		if (!posi)
			return (0);
		inf->argv[0] = posi;
	}
	return (1);
}

/**
 * rep_var - replaces vars
 * @inf: struct
 * Return: 1 or 0 otherwise
 */
int rep_var(info_t *inf)
{
	int iii = 0;
	list_t *n;

	for (iii = 0; inf->argv[iii]; iii++)
	{
		if (inf->argv[iii][0] != '$' || !inf->argv[iii][1])
			continue;

		if (!cmp_str(inf->argv[iii], "$?"))
		{
			rep_str(&(inf->argv[iii]),
				dupli_sat(convnum(inf->status, 10, 0)));
			rep_str(&(inf->argv[iii]),
				dupli_sat(convnum(inf->status, 10, 0)));
			continue;
		}
		if (!cmp_str(inf->argv[iii], "$$"))
		{
			rep_str(&(inf->argv[iii]),
				dupli_sat(convnum(getpid(), 10, 0)));
			rep_str(&(inf->argv[iii]),
				dupli_sat(convnum(getpid(), 10, 0)));
			continue;
		}
		n = n_start(inf->env, &inf->argv[iii][1], '=');
		if (n)
		{
			rep_str(&(inf->argv[iii]),
				dupli_sat(char_str(n->str, '=') + 1));
			continue;
		}
		rep_str(&inf->argv[iii], dupli_sat(""));
	}
	return (0);
}

/**
 * rep_str - rep string
 * @o: old string
 * @n: new string
 * Return: 1 or 0 otherwise
 */
int rep_str(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
