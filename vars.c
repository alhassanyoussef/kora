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
<<<<<<< HEAD
		posi = _strdup(posi + 1);
		if (!posi)
=======
		p = dupli_sat(p + 1);
		if (!p)
>>>>>>> 87d3fb219a3b097ecdf6539deb4eee44e6c4f40e
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
<<<<<<< HEAD
			rep_str(&(inf->argv[iii]),
				_strdup(convnum(inf->status, 10, 0)));
=======
			replace_string(&(info->argv[i]),
				dupli_sat(convnum(info->status, 10, 0)));
>>>>>>> 87d3fb219a3b097ecdf6539deb4eee44e6c4f40e
			continue;
		}
		if (!cmp_str(inf->argv[iii], "$$"))
		{
<<<<<<< HEAD
			rep_str(&(inf->argv[iii]),
				_strdup(convnum(getpid(), 10, 0)));
=======
			replace_string(&(info->argv[i]),
				dupli_sat(convnum(getpid(), 10, 0)));
>>>>>>> 87d3fb219a3b097ecdf6539deb4eee44e6c4f40e
			continue;
		}
		n = n_start(inf->env, &inf->argv[iii][1], '=');
		if (n)
		{
<<<<<<< HEAD
			rep_str(&(inf->argv[iii]),
				_strdup(char_str(n->str, '=') + 1));
			continue;
		}
		rep_str(&inf->argv[iii], _strdup(""));
=======
			replace_string(&(info->argv[i]),
				dupli_sat(char_str(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], dupli_sat(""));
>>>>>>> 87d3fb219a3b097ecdf6539deb4eee44e6c4f40e

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
