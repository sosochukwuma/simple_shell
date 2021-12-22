#include "hsh.h"

/**
 * _putchar - writes the character c to stdout
 *
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _strcat - concatenates two strings
 *
 * @dest: the first string & destination
 * @src: the second string
 *
 * Return: a pointer to the destination string
 */

char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	if (dest != NULL)
	{
		while (dest[i])
			i++;
	}

	if (src != NULL)
	{
		while (src[j] != '\0')
		{
			dest[i + j] = src[j];
			j++;
		}
	}
	dest[i + j] = '\0';
	return (dest);
}

/**
 * _strtok - respin of strtok()
 *
 * @str: string to split
 * @delim: string of delimiters
 *
 * Return: pointer to next token
 */

char *_strtok(char *str, char *delim)
{
	char *end = NULL;
	static char *ptrtok;

	if (str == NULL)
		str = ptrtok;

	if (*str == '\0')
	{
		ptrtok = str;
		return (NULL);
	}

	str = str + _strspn(str, delim);
	if (*str == '\0')
	{
		ptrtok = str;
		return (NULL);
	}

	end = str + _strcspn(str, delim);
	if (*end == '\0')
	{
		ptrtok = end;
		return (str);
	}

	*end = '\0';
	ptrtok = end + 1;

	return (str);
}

/**
 * _strspn - Gets the length of a prefix substring.
 *
 * @s: string to be searched
 * @accept: string of accepted chars to match
 *
 * Return: the index of the last matching char
 */

unsigned int _strspn(char *s, char *accept)
{
	unsigned int i = 0;

	while (s[i])
	{
		if (_strchr(accept, s[i]) != NULL)
			i++;
		else
			break;
	}

	return (i);
}

/**
 * _strcspn - Gets the length of a prefix substring NOT matching a given string
 *
 * @s: string to be searched
 * @reject: string of rejected chars to match
 *
 * Return: the index of the first non matching char
 */

unsigned int _strcspn(char *s, char *reject)
{
	unsigned int i = 0;

	while (s[i])
	{
		if (_strchr(reject, s[i]) == NULL)
			i++;
		else
			break;
	}

	return (i);
}
