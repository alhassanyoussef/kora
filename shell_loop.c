#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clinformation(info);
		if (inter_act(info))
			_puts("$ ");
		 write_char(BUF_FLUSH);
		r = _youmi(info);
		if (r != -1)
		{
			s_information(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (inter_act(info))
			_putchar('\n');
		frinformation(info, 0);
	}
	write_history(info);
	frinformation(info, 1);
	if (!inter_act(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", my_enviro},
		{"help", my_help},
		{"history", my_date},
		{"setenv", my_set_env},
		{"unsetenv", my_unset_env},
		{"cd", my_cd},
		{"alias", alias_mine},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (cmp_str(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_that_deli(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = catch_pat(info, get_enviro(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((inter_act(info) || get_enviro(info, "PATH=")
			|| info->argv[0][0] == '/') && hello_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printerr(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, catch_env(info)) == -1)
		{
			frinformation(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printerr(info, "Permission denied\n");
		}
	}
}
