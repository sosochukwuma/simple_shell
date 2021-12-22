#include "hsh.h"

/**
 * main - simple shell
 *
 * @ac: argument count
 * @av: argument values
 * @env: environment
 *
 * Return: always 0
 */

int main(int ac, char **av, char **env)
{
	int status = 1;
	data_t *data;

	signal(SIGINT, sig_ign);

	data = data_new(env, av);

	if (ac > 1)
	{
		/*filemode*/
	}
	else
	{
		while (status)
		{
			if (isatty(STDIN_FILENO))
				_puts(PROMPT);
			hsh_getline(data);
			if (data->line[0] != '\n')
			{
				data = hsh_tokens(data);
				status = hsh_exec(data);
				free(data->toks);
			}
			free(data->line);
			data->cmd_cnt += 1;
		}
	}

	return (0);
}

/**
 * data_new - Populates the data struct
 *
 * @env: environment array
 * @argv: argv
 *
 * Return: a data_t struct
 */

data_t *data_new(char **env, char **argv)
{
	data_t *new = NULL;

	new = malloc(sizeof(data_t));
	if (new)
	{
		dupl_env(new, env);
		dupl_argv(new, argv);
		new->cmd_cnt = 1;
		new->line = NULL;
		new->toks = NULL;
	}
	else
		return (NULL);

	return (new);
}

/**
 * dupl_env - Duplicates the **env
 *
 * @data: the data struct
 * @env: the environment
 *
 * Return: a duplicate of the env in data->env
 */

data_t *dupl_env(data_t *data, char **env)
{
	int i = 0, j = 0;

	while (env[i])
		i++;
	data->env = malloc(sizeof(char *) * (i + 1));
	if (!data->env)
		return (NULL);

	while (env[j])
	{
		data->env[j] = _strdup(env[j]);
		j++;
	}

	data->env[j] = NULL;

	return (data);
}

/**
 * dupl_argv - Duplicates the **argv
 *
 * @data: the data struct
 * @argv: the argv
 * Return: a duplicate of argv in data->argv
 */

data_t *dupl_argv(data_t *data, char **argv)
{
	int i = 0, j = 0;

	while (argv[i])
		i++;
	data->argv = malloc(sizeof(char *) * (i + 1));
	if (!data->argv)
		return (NULL);

	while (argv[j])
	{
		data->argv[j] = _strdup(argv[j]);
		j++;
	}

	data->argv[j] = NULL;

	return (data);
}
