#include "hsh.h"

/**
 * hsh_err - displays error messages
 *
 * @data: the data struct
 * @msg: error message to display
 *
 * Return: the data struct
 */

void hsh_err(data_t *data, char *msg)
{
	char errmsg[200];
	char *cnt = _itoa(data->cmd_cnt);

	_strcpy(errmsg, data->argv[0]);
	_strcat(errmsg, ": ");
	_strcat(errmsg, cnt);
	_strcat(errmsg, ": ");
	_strcat(errmsg, data->toks[0]);
	_strcat(errmsg, ": ");
	_strcat(errmsg, msg);
	_strcat(errmsg, "\n");

	write(2, errmsg, _strlen(errmsg));
	free(cnt);
}
