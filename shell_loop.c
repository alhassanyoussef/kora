#include "shell.h"

/**
 * sh - shell
 * @information: the parameter
 * @arvec: argument vec
 * Return: 0 while success, 1 while error
 */
int sh(info_t *information, char **arvec)
{
	ssize_t rrr = 0;
	int builtret = 0;

	while (rrr != -1 && builtret != -2)
	{
		clinformation(information);
		if (inter_act(information))
			_puts("$ ");
		 write_char(BUF_FLUSH);
		rrr = _youmi(information);
		if (rrr != -1)
		{
			s_information(information, arvec);
			builtret = f_built(information);
			if (builtret == -1)
				f_cm(information);
		}
		else if (inter_act(information))
			_putchar('\n');
		frinformation(information, 0);
	}
	write_history(information);
	frinformation(information, 1);
	if (!inter_act(information) && information->status)
		exit(information->status);
	if (builtret == -2)
	{
		if (information->err_num == -1)
			exit(information->status);
		exit(information->err_num);
	}
	return (builtret);
}

/**
 * f_built - builtin command
 * @information: the parameter
 * Return: -1 not found, 0 if successfully,1 not success,-2 if exit()
 */
int f_built(info_t *information)
{
	int iii, builtinret = -1;
	builtin_table builttbl[] = {
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

	for (iii = 0; builttbl[iii].type; iii++)
		if (cmp_str(information->argv[0], builttbl[iii].type) == 0)
		{
			information->line_count++;
			builtinret = builttbl[iii].func(information);
			break;
		}
	return (builtinret);
}

/**
 * f_cm - command
 * @inf: parameter
 * Return:
 */
void f_cm(info_t *inf)
{
	char *p = NULL;
	int iii, kkk;

	inf->path = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (iii = 0, kkk = 0; inf->arg[iii]; iii++)
		if (!is_that_deli(inf->arg[iii], " \t\n"))
			kkk++;
	if (!kkk)
		return;

	p = catch_pat(inf, get_enviro(inf, "PATH="), inf->argv[0]);
	if (p)
	{
		inf->path = p;
		fk_cm(inf);
	}
	else
	{
		if ((inter_act(inf) || get_enviro(inf, "PATH=")
			|| inf->argv[0][0] == '/') && hello_cmd(inf, inf->argv[0]))
			fk_cm(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			printerr(inf, "not found\n");
		}
	}
}

/**
 * fk_cm - forks
 * @inf: parameter
 * Return:
 */
void fk_cm(info_t *inf)
{
	pid_t ch_pid;

	ch_pid = fork();
	if (ch_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (ch_pid == 0)
	{
		if (execve(inf->path, inf->argv, catch_env(inf)) == -1)
		{
			frinformation(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				printerr(inf, "Permission denied\n");
		}
	}
}
