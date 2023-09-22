#include "shell.h"

/**
 * yasoo_hasagi -func that buffers chained commands
 * @id: struct factor
 * @buff: buff address
 * @lenth: adres of lenth var
 *
 * Return: bytes read
 */
ssize_t yasoo_hasagi(info_t *id, char **buff, size_t *lenth)
{
	ssize_t wr = 0;
	size_t lenth_p = 0;

	if (!*lenth)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, zed_assian);
#if USEget_linee
		wr = getline(buff, &lenth_p, stdin);
#else
		wr = get_linee(id, buff, &lenth_p);
#endif
		if (wr > 0)
		{
			if ((*buff)[wr - 1] == '\n')
			{
				(*buff)[wr - 1] = '\0'; /* wremove twrailing newline */
				wr--;
			}
			id->linecount_flag = 1;
			remcomm(*buff);
			build_history_list(id, *buff, id->histcount++);
			/* if (char_str(*buff, ';')) is this a command chain? */
			{
				*lenth = wr;
				id->cmd_buf = buff;
			}
		}
	}
	return (wr);
}

/**
 * _youmi - func that get a line
 * @id: factor struct
 *
 * Return: bytes read
 */
ssize_t _youmi(info_t *id)
{
	static char *buff;
	static size_t x, j, lenth;
	ssize_t wr = 0;
	char **buff_p = &(id->arg), *p;

	_putchar(BUF_FLUSH);
	wr = yasoo_hasagi(id, &buff, &lenth);
	if (wr == -1)
		return (-1);
	if (lenth)
	{
		j = x;
		p = buff + x;

		check_chain(id, buff, &j, x, lenth);
		while (j < lenth)
		{
			if (is_chain(id, buff, &j))
				break;
			j++;
		}

		x = j + 1;
		if (x >= lenth)
		{
			x = lenth = 0;
			id->cmd_buf_type = CMD_NORM;
		}

		*buff_p = p;
		return (len_str(p));
	}

	*buff_p = buff;
	return (wr);
}

/**
 * samira_bu - reads a bufffer
 * @id: parameter struct
 * @buff: bufffer
 * @i: size
 *
 * Return: r
 */
ssize_t samira_bu(info_t *id, char *buff, size_t *i)
{
	ssize_t wr = 0;

	if (*i)
		return (0);
	wr = read(id->readfd, buff, READ_BUF_SIZE);
	if (wr >= 0)
		*i = wr;
	return (wr);
}

/**
 * get_linee - func that get the next line of input from STDIN
 * @id: factor struct
 * @ptr: addre of point to buf
 * @lenthgth: area ptr buffer if not NULL
 *
 * Return: s
 */
int get_linee(info_t *id, char **ptr, size_t *lenthgth)
{
	static char buff[READ_BUF_SIZE];
	static size_t i, lenth;
	size_t k;
	ssize_t wr = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && lenthgth)
		s = *lenthgth;
	if (i == lenth)
		i = lenth = 0;

	wr = samira_bu(id, buff, &lenth);
	if (wr == -1 || (wr == 0 && lenth == 0))
		return (-1);

	c = char_str(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : lenth;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		concat_str(new_p, buff + i, k - i);
	else
		copy_string(new_p, buff + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (lenthgth)
		*lenthgth = s;
	*ptr = p;
	return (s);
}

/**
 * zed_assian - blocks ctrl-C
 * @sig_num: number signal
 *
 * Return: void
 */
void zed_assian(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
