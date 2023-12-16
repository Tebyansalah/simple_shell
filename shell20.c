#include "shell.h" 
 
/** 
 * chain_dem - test if current char in buffer is a chain delimeter 
 * @sd: the parameter struct 
 * @buf: the char buffer 
 * @p: address of current position in buf 
 * 
 * Return: 1 if chain delimeter, 0 otherwise 
 */ 
int chain_dem(sd_t *sd, char *buf, size_t *p) 
{ 
	size_t j = *p; 
 
	if (buf[j] == '|' && buf[j + 1] == '|') 
	{ 
		buf[j] = 0; 
		j++; 
		sd->cmd_buf_type = CMD_OR; 
	} 
	else if (buf[j] == '&' && buf[j + 1] == '&') 
	{ 
		buf[j] = 0; 
		j++; 
		sd->cmd_buf_type = CMD_AND; 
	} 
	else if (buf[j] == ';') /* found end of this command */ 
	{ 
		buf[j] = 0; /* replace semicolon with null */ 
		sd->cmd_buf_type = CMD_CHAIN; 
	} 
	else 
		return (0); 
	*p = j; 
	return (1); 
} 
 
/** 
 * chain_stat - checks we should continue chaining based on last status 
 * @sd: the parameter struct 
 * @buf: the char buffer 
 * @p: address of current position in buf 
 * @i: starting position in buf 
 * @len: length of buf 
 * 
 * Return: Void 
 */ 
void chain_stat(sd_t *sd, char *buf, size_t *p, size_t i, size_t len) 
{ 
	size_t j = *p; 
 
	if (sd->cmd_buf_type == CMD_AND) 
	{ 
		if (sd->status) 
		{ 
			buf[i] = 0; 
			j = len; 
		} 
	} 
	if (sd->cmd_buf_type == CMD_OR) 
	{ 
		if (!sd->status) 
		{ 
			buf[i] = 0; 
			j = len; 
		} 
	} 
 
	*p = j; 
} 
 
/** 
 * rep_tokenalias - replaces an aliases in the tokenized string 
 * @sd: the parameter struct 
 * 
 * Return: 1 if replaced, 0 otherwise 
 */ 
int rep_tokenalias(sd_t *sd) 
{ 
	int i; 
	list_t *node; 
	char *p; 
 
	for (i = 0; i < 10; i++) 
	{ 
		node = node_starts_with(sd->alias, sd->argv[0], '='); 
		if (!node) 
			return (0); 
		free(sd->argv[0]); 
		p = _charinsr(node->sr, '='); 
		if (!p) 
			return (0); 
		p = _strdup(p + 1); 
		if (!p) 
			return (0); 
		sd->argv[0] = p; 
	} 
	return (1); 
} 
 
/** 
 * replace_vars - replaces vars in the tokenized string 
 * @sd: the parameter struct 
 * 
 * Return: 1 if replaced, 0 otherwise 
 */ 
int replace_vars(sd_t *sd) 
{ 
	int i = 0; 
	list_t *node; 
 
	for (i = 0; sd->argv[i]; i++) 
	{ 
		if (sd->argv[i][0] != '$' || !sd->argv[i][1]) 
			continue; 
 
		if (!_towstr(sd->argv[i], "$?")) 
		{ 
			replace_string(&(sd->argv[i]), 
				_strdup(_cfunction(sd->status, 10, 0))); 
			continue; 
		} 
		if (!_towstr(sd->argv[i], "$$")) 
		{ 
			replace_string(&(sd->argv[i]), 
				_strdup(_cfunction(getpid(), 10, 0))); 
			continue; 
		} 
		node = node_starts_with(sd->env, &sd->argv[i][1], '='); 
		if (node) 
		{ 
			replace_string(&(sd->argv[i]), 
				_strdup(_charinsr(node->sr, '=') + 1)); 
			continue; 
		} 
		replace_string(&sd->argv[i], _strdup("")); 
 
	} 
	return (0); 
} 
 
/** 
 * replace_string - replaces string 
 * @old: address of old string 
 * @new: new string 
 * 
 * Return: 1 if replaced, 0 otherwise 
 */ 
int replace_string(char **old, char *new) 
{ 
	free(*old); 
	*old = new; 
	return (1); 
} 
