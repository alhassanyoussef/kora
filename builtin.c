#include "shell.h"

/**
 * my_exit - shell exit
 * @info: used to save the prototype
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int my_exit(info_t *info)
{
	int exitchecker;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitchecker = err(info->argv[1]);
		if (exitchecker == -1)
		{
			info->status = 2;
			printerr(info, "Illegal number: ");
			print_str(info->argv[1]);
			write_char('\n');
			return (1);
		}
		info->err_num = err(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * my_cd - change directory
 * @info: used to save the prototype
 *  Return: Always 0
 */
int my_cd(info_t *info)
{
	char *st, *dir, buffer[1024];
	int chdir_ret;

	st = getcwd(buffer, 1024);
	if (!st)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_enviro(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = get_enviro(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (cmp_str(info->argv[1], "-") == 0)
	{
		if (!get_enviro(info, "OLDPWD="))
		{
			_puts(st);
			write_char('\n');
			return (1);
		}
		_puts(get_enviro(info, "OLDPWD=")), write_char('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = get_enviro(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		printerr(info, "can't cd to ");
		print_str(info->argv[1]), write_char('\n');
	}
	else
	{
		seraphine_str(info, "OLDPWD", get_enviro(info, "PWD="));
		seraphine_str(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - change current dir of the process
 * @info: used to save the prototype
 *  Return: Always 0
 */
int my_help(info_t *info)
{
	char **argg_array;

	argg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argg_array);
	return (0);
}

