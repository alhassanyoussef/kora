#include "shell.h"

/**
 * hello_cmd - func that checks if a file is an exec command
 * @info: struct info
 * @pa: file path
 *
 * Return: 1 if true, 0 otherwise
 */
int hello_cmd(info_t *info, char *pa)
{
	struct stat st;

	(void)info;
	if (!pa || stat(pa, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupli_charss - function that duplicate chars
 * @roadst: string path
 * @begin: index begining
 * @hold:  index holding
 *
 * Return: pointer to new buffer
 */
char *dupli_charss(char *roadst, int begin, int hold)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = begin; i < hold; i++)
		if (roadst[i] != ':')
			buf[k++] = roadst[i];
	buf[k] = 0;
	return (buf);
}

/**
 * catch_pat - func that find the path string
 * @info: struct info
 * @roadst: string path
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *catch_pat(info_t *info, char *roadst, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!roadst)
		return (NULL);
	if ((len_str(cmd) > 2) && push_hard(cmd, "./"))
	{
		if (hello_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!roadst[i] || roadst[i] == ':')
		{
			path = dupli_charss(roadst, curr_pos, i);
			if (!*path)
				cat_str(path, cmd);
			else
			{
				cat_str(path, "/");
				cat_str(path, cmd);
			}
			if (hello_cmd(info, path))
				return (path);
			if (!roadst[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
