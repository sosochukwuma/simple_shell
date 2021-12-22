#ifndef HSH_H
#define HSH_H

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <limits.h>

/* MACROS */
#define TOK_DELIM " \n\t\r\a"
#define PROMPT "$ "

/* STRUCTS */

/**
 * struct data_s - the data structure
 *
 * @toks: command tokens
 * @line: line returned from getline
 * @env: the environment array
 * @argv: the argv array
 * @cmd_cnt: number of commands typed since launch
 */

typedef struct data_s
{
	char *line;
	char **argv;
	char **env;

	char **toks;

	int cmd_cnt;
} data_t;

/* BUILTINS */

int hsh_cd(data_t *data);
int hsh_help(data_t *data);
int hsh_exit(data_t *data);
int hsh_env(data_t *data);
int hsh_setenv(data_t *data);
int hsh_unsetenv(data_t *data, char *name);
int hsh_history(data_t *data);

/* STRING UTILS */

int _strlen(char *str);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);
void _puts(char *str);
int _strcmp(char *s1, char *s2);
int _putchar(char c);
char *_strcat(char *s1, char *s2);
char *_strtok(char *str, char *delim);
unsigned int _strspn(char *s, char *accept);
unsigned int _strcspn(char *s, char *reject);
char *_strchr(char *s, char c);
int wordcnt(char *str, char delim);
int _strncmp(char *s1, char *s2, size_t n);
void rev_string(char *str);

/* MISC UTILS */
void sig_ign(int sig_num);

/* DATA UTILS */
data_t *data_new(char **env, char **argv);
data_t *dupl_env(data_t *data, char **env);
data_t *dupl_argv(data_t *data, char **argv);

/* MATH UTILS */
int _atoi(char *s);
char *_itoa(int i);

/* MEM UTILS */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_star(char **args, int n);

/* ENV UTILS */
char *_getenv(data_t *data, char *name);
int _setenv(data_t *data, char *name, char *value);
int _unsetenv(data_t *data, char *name);

/* ERR UTILS */
void errcmp(data_t *data, char *compare);
void hsh_err(data_t *data, char *msg);

/* MAIN FUNCTIONS */

data_t *hsh_getline(data_t *data);
data_t *hsh_tokens(data_t *data);
int hsh_exec(data_t *data);
data_t *hsh_checkpath(data_t *data);
data_t *hsh_checkpath2(data_t *data, char **paths);
int hsh_check_builtins(data_t *data);

#endif
