#include "hsh.h"

/**
 * _getenv - respin of getenv()
 *
 * @data: the data struct
 * @name: Requested key
 *
 * Return: Value of requested key
 */

char *_getenv(data_t *data, char *name)
{
	int i = 0, j = 0;

	if (!data->env)
	{
		hsh_err(data, "_getenv: failed to fetch environment");
		return (NULL);
	}


	while (data->env[i])
	{
		while (data->env[i][j] == name[j])
		{
			j++;
			if (data->env[i][j] == '=')
			{
				j++;
				return (&data->env[i][j]);
			}
		}
		i++;
	}

	return (NULL);
}

/**
 * _setenv - sets an env variable
 *
 * @data: the data struct
 * @name: name of the variable
 * @value: value of the variable
 *
 * Return: Always 0
 */

int _setenv(data_t *data, char *name, char *value)
{
	int i = 0, osizenv = 0, nsizenv = 0;
	int tok1siz = _strlen(name), tok2siz = _strlen(value);

	if (name == NULL || value == NULL)
		hsh_err(data, "_setenv: missing parameter");
	else if (!data->env)
		hsh_err(data, "_setenv: failed to fetch environment");
	else
	{
		if (_getenv(data, name))
			_unsetenv(data, name);

		while (data->env[i] != NULL)
			i++;

		osizenv = sizeof(char *) * (i + 1);
		nsizenv = sizeof(char *) * (i + 2);
		data->env = _realloc(data->env, osizenv, nsizenv);
		if (data->env)
		{
			data->env[i] = malloc(sizeof(char) * (tok1siz + tok2siz + 2));
			if (data->env[i])
			{
				_strcpy(data->env[i], name);
				_strcat(data->env[i], "=");
				_strcat(data->env[i], value);

				i++;
				data->env[i] = NULL;
			}
			else
				hsh_err(data, "_setenv: malloc failure");
		}
		else
			hsh_err(data, "_setenv: _realloc failure");
	}
	return (1);
}

/**
 * _unsetenv - unsets an environment variable
 *
 * @data: the data struct
 * @name: name of varible
 *
 * Return: Always 1
 */

int _unsetenv(data_t *data, char *name)
{
	int i = 0, j = 0, oldS, newS;

	if (!name)
	{
		hsh_err(data, "_unsetenv: missing pameters");
		return (0);
	}
	else if (!data->env)
	{
		hsh_err(data, "_unsetenv: failed to fetch environment");
		return (0);
	}

	while (data->env[i])
		i++;

	while (_strncmp(data->env[j], name, _strlen(name)) != 0)
	{
		j++;
		if (j == i)
		{
			hsh_err(data, "_unsetenv: variable not found");
			return (1);
		}
	}

	free(data->env[j]);

	while (j < i)
	{
		data->env[j] = data->env[j + 1];
		j++;
	}

	oldS = sizeof(char *) * (i + 2);
	newS = sizeof(char *) * (i + 1);
	data->env = _realloc(data->env, oldS, newS);

	return (1);
}

