#include "hsh.h"

/**
 * hsh_check_builtins - checks for builtins
 *
 * @data: the data struct
 *
 * Return: 1 if success, 0 if failure
 */

int hsh_check_builtins(data_t *data)
{
	if (data->toks[0] == NULL)
		return (-1);

	if (_strcmp(data->toks[0], "cd") == 0)
		return (hsh_cd(data));
	if (_strcmp(data->toks[0], "help") == 0)
		return (hsh_help(data));
	if (_strcmp(data->toks[0], "exit") == 0)
		return (hsh_exit(data));
	if (_strcmp(data->toks[0], "env") == 0)
		return (hsh_env(data));
	if (_strcmp(data->toks[0], "setenv") == 0)
		return (hsh_setenv(data));
	if (_strcmp(data->toks[0], "unsetenv") == 0)
		return (hsh_unsetenv(data, data->toks[1]));
	return (0);
}

/**
 * hsh_env - print environment variables
 *
 * @data: the data struct
 *
 * Return: Always 1
 */

int hsh_env(data_t *data)
{
	int i;

	i = 0;

	if (!data->env)
	{
		hsh_err(data, "couldn't find environment");
		return (1);
	}

	while (data->env[i])
	{
		_puts(data->env[i]);
		_putchar('\n');
		i++;
	}
	return (1);
}

/**
 * hsh_cd - changes directory
 *
 * @data: the data struct
 *
 * Return: 1 if success, -1 if folder doesn't exist
 */

int hsh_cd(data_t *data)
{
	char *path;
	char errmsg[200] = "can't cd to ";
	char *cwd = NULL;

	if (!data->toks[1])
	{
		if (_getenv(data, "HOME"))
			path = _getenv(data, "HOME");
		else
			return (1);
	}
	else if (_strcmp(data->toks[1], "-") == 0)
	{
		if (_getenv(data, "OLDPWD"))
		{
			path = _getenv(data, "OLDPWD");
			_puts(path);
			_putchar('\n');
		}
		else
		{
			cwd = getcwd(cwd, 0);
			_puts(cwd);
			_putchar('\n');
			free(cwd);
			return (1);
		}
	}
	else
		path = data->toks[1];
	if (chdir(path) == -1)
		hsh_err(data, _strcat(errmsg, data->toks[1]));
	else
	{
		cwd = getcwd(cwd, 0);
		_setenv(data, "OLDPWD", _getenv(data, "PWD"));
		_setenv(data, "PWD", cwd);
	}
	free(cwd);
	return (1);
}

/**
 * hsh_exit - Exits the shell
 *
 * @data: the data struct
 *
 * Return: -1 if failure
 */

int hsh_exit(data_t *data)
{
	int i = 0, j = 0, k = 0, l = 0;
	char errmsg[200] = "";

	if (data->toks[1])
	{
		i = _atoi(data->toks[1]);
		while (data->toks[1][l])
		{
			if (data->toks[1][l] < '0' || data->toks[1][l] > '9')
			{
				_strcat(errmsg, "Illegal number: ");
				_strcat(errmsg, data->toks[1]);
				hsh_err(data, errmsg);
				return (2);
			}
			else if (i && (i < 0 || i > INT_MAX))
			{
				_strcat(errmsg, "Illegal number: ");
				_strcat(errmsg, data->toks[1]);
				hsh_err(data, errmsg);
				return (1);
			}
			l++;
		}
	}
	while (data->env[j])
		j++;
	while (data->argv[k])
		k++;
	free_star(data->argv, k);
	free_star(data->env, j);
	free(data->toks);
	free(data->line);
	free(data);
	_exit(i);

	return (-1);
}

/**
 * hsh_help - user help
 *
 * @data: the data struct
 *
 * Return: 1 if success, -1 if failure
 */

int hsh_help(data_t *data)
{
	int i = 0, len;
	char errmsg[200];
	char *builtin_str[] = {
		"cd", "help", "exit", "env", "setenv", "unsetenv", NULL};

	len = _strlen(data->toks[1]);
	if (data->toks[1])
	{
		if (_strncmp(data->toks[1], "cd", len) == 0)
			_puts("Usage : cd [directory]\n");
		else if (_strncmp(data->toks[1], "help", len) == 0)
			_puts("Usage : help [builtin]\n");
		else if (_strncmp(data->toks[1], "exit", len) == 0)
			_puts("Usage : exit [argument]\n");
		else if (_strncmp(data->toks[1], "env", len) == 0)
			_puts("Usage : env\n");
		else if (_strncmp(data->toks[1], "setenv", len) == 0)
			_puts("Usage : setenv [name] [value]\n");
		else if (_strncmp(data->toks[1], "unsetenv", len) == 0)
			_puts("Usage : unsetenv [name]\n");
		else
		{
			_strcat(errmsg, "no help topics match '");
			_strcat(errmsg, data->toks[1]);
			_strcat(errmsg, "'.  Try `help help'.");
		}
	}
	else
	{
		while (builtin_str[i])
		{
			_puts("Usage : help [");
			_puts(builtin_str[i++]);
			_puts("]\n");
		}
	}
	return (1);
}
