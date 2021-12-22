#include "hsh.h"

/**
 * _strchr - locates a character in a string
 *
 * @s: the string to look inside
 * @c: the character to find
 *
 * Return: a pointer to the first occurence of c in s, or NULL if not found
 */

char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	if (s[i] == c)
		return (s + i);
	return (NULL);
}

/**
 * wordcnt - counts words in string separated by delim
 *
 * @str: pointer to string
 * @delim: delimiter to check against
 *
 * Return: the number of words in that string
 */

int wordcnt(char *str, char delim)
{
	int i = 0, cnt = 0;

	while (str[i])
	{
		if (str[i] == delim)
			i++;
		else
		{
			while (str[i] && str[i] != delim)
				i++;
			cnt++;
		}
	}
	return (cnt);
}

/**
 * _strncmp - compares 2 strings up to n bytes
 *
 * @s1: first string
 * @s2: second string
 * @n: number of chars to compare
 *
 * Return: diff between first two different chars
 */


int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i = 0;

	while (s1[i] && s2[i] && i <= n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	return (0);
}

/**
 * rev_string - reverses a string
 *
 * @str: the string to be reversed
 */

void rev_string(char *str)
{
	int i, j = 0, len = (_strlen(str) - 1);
	char tmp;

	for (i = len; i > j; i--)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		j++;
	}
}

/**
 * sig_ign - handler for SIGINT
 *
 * @sig_num: signal to handle
 */

void sig_ign(int sig_num)
{
	if (sig_num == SIGINT)
	{
		_putchar('\n');
		_puts(PROMPT);
	}
}
