#include "hsh.h"

/**
 * hsh_getline - gets the line
 *
 * @data: the data struct
 *
 * Return: A string containing the command to execute
 */

data_t *hsh_getline(data_t *data)
{
	size_t buf = 0;
	int j = 0, k = 0;

	if ((getline(&(data->line), &buf, stdin)) == EOF)
	{
		while (data->env[j])
			j++;

		while (data->argv[k])
			k++;

		free_star(data->argv, k);
		free_star(data->env, j);
		free(data->line);
		free(data);
		exit(0);
	}
	return (data);
}

/**
 * hsh_tokens - splits the line
 *
 * @data: the data struct
 *
 * Return: char** containing all tokens in the struct
 */

data_t *hsh_tokens(data_t *data)
{
	int i = 0, num_toks = 0;
	char *delim = TOK_DELIM, *tmp = NULL;

	num_toks = wordcnt(data->line, ' ');

	data->toks = malloc(sizeof(char *) * (num_toks + 1));

	if (data->toks)
	{
		tmp = _strtok(data->line, delim);
		while (tmp != NULL)
		{
			if (tmp && tmp[0] == '#')
				break;
			data->toks[i++] = tmp;
			tmp = _strtok(NULL, delim);
		}

		data->toks[i] = NULL;
	}
	else
		hsh_err(data, "couldn't allocate memory");

	return (data);
}

/**
 * hsh_exec - executes a command from its tokens
 *
 * @data: the data struct
 *
 * Return: a status code
 */

int hsh_exec(data_t *data)
{
	pid_t child_pid;
	int status;
	char *tmp = data->toks[0];

	if (hsh_check_builtins(data))
		return (1);

	hsh_checkpath(data);

	if (data->toks[0] == NULL)
		return (1);

	child_pid = fork();
	if (child_pid == -1)
	{
		hsh_err(data, "unable to fork");
		return (1);
	}
	if (child_pid == 0)
	{
		status = execve(data->toks[0], data->toks, data->env);
		_exit(status);
	}
	else
	{
		wait(&status);
	}

	if (_strcmp(data->toks[0], tmp) != 0)
		free(data->toks[0]);

	return (1);
}

/**
 * hsh_checkpath - checks command against all PATH folders
 *
 * @data: the data struct
 *
 * Return: the data struct
 */

data_t *hsh_checkpath(data_t *data)
{
	char *path, *origtok = _strdup(data->toks[0]);
	char **paths;
	int i = 0, num_toks = 0, cmp1, cmp2, cmp3;

	cmp1 = _strncmp(data->toks[0], "/", 1);
	cmp2 = _strncmp(data->toks[0], "./", 2);
	cmp3 = _strncmp(data->toks[0], "../", 3);
	if (cmp1 == 0 || cmp2 == 0 || cmp3 == 0)
	{
		if (access(data->toks[0], X_OK) != 0)
			hsh_err(data, "not found");
		free(origtok);
		return (data);
	}
	else
	{
		path = _strdup(_getenv(data, "PATH"));
		num_toks = wordcnt(path, ':');
		paths = malloc(sizeof(char *) * (num_toks + 2));
		if (!paths)
		{
			free(origtok);
			free(path);
			return (data);
		}
		while (i <= num_toks)
		{
			if (i == 0)
				paths[i++] = _strtok(path, ":");
			else
				paths[i++] = _strtok(NULL, ":");
		}
		hsh_checkpath2(data, paths);
		free(path);
		free(paths);
	}
	if (_strncmp(data->toks[0], origtok, _strlen(origtok)) == 0)
		hsh_err(data, "not found");
	free(origtok);
	return (data);
}

/**
 * hsh_checkpath2 - checks command against all PATH folders
 *
 * @data: the data struct
 * @paths: all paths from PATH
 *
 * Return: the data struct
 */

data_t *hsh_checkpath2(data_t *data, char **paths)
{
	int j = 0, lentok = 0;
	char *tmp = NULL;

	while (paths[j])
	{
		lentok = _strlen(data->toks[0]);
		tmp = malloc(sizeof(char) * (_strlen(paths[j]) + lentok + 2));
		_strcat(_strcat(_strcpy(tmp, paths[j++]), "/"), data->toks[0]);
		if (!tmp)
		{
			hsh_err(data, "couldn't allocate memory");
			return (data);
		}
		if (access(tmp, X_OK) == 0)
		{
			data->toks[0] = _strdup(tmp);
			free(tmp);
			break;
		}
		free(tmp);

	}
	return (data);
}
