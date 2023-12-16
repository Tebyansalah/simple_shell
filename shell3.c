#include "shell.h" 
 
/** 
 * _hslist - displays the history list, one command by line, preceded 
 *              with line numbers, starting at 0. 
 * @sd: Structure containing potential arguments. Used to maintain 
 *        constant function prototype. 
 *  Return: Always 0 
 */ 
int _hslist(sd_t *sd) 
{ 
	p_list(sd->history); 
	return (0); 
} 
 
/** 
 * _unalais - sets alias to string 
 * @sd: parameter struct 
 * @sr: the string alias 
 * 
 * Return: Always 0 on success, 1 on error 
 */ 
int _unalais(sd_t *sd, char *sr) 
{ 
	char *p, c; 
	int ret; 
 
	p = _charinsr(sr, '='); 
	if (!p) 
		return (1); 
	c = *p; 
	*p = 0; 
	ret = delete_node_at_index(&(sd->alias), 
		get_node_index(sd->alias, node_starts_with(sd->alias, sr, -1))); 
	*p = c; 
	return (ret); 
} 
 
/** 
 * _salais - sets alias to string 
 * @sd: parameter struct 
 * @sr: the string alias 
 * 
 * Return: Always 0 on success, 1 on error 
 */ 
int _salais(sd_t *sd, char *sr) 
{ 
	char *p; 
 
	p = _charinsr(sr, '='); 
	if (!p) 
		return (1); 
	if (!*++p) 
		return (_unalais(sd, sr)); 
 
	_unalais(sd, sr); 
	return (add_node_end(&(sd->alias), sr, 0) == NULL); 
} 
 
/** 
 * _palais - prints an alias string 
 * @node: the alias node 
 * 
 * Return: Always 0 on success, 1 on error 
 */ 
int _palais(list_t *node) 
{ 
	char *p = NULL, *a = NULL; 
 
	if (node) 
	{ 
		p = _charinsr(node->sr, '='); 
		for (a = node->sr; a <= p; a++) 
			_putchar(*a); 
		_putchar('\''); 
		_puts(p + 1); 
		_puts("'\n"); 
		return (0); 
	} 
	return (1); 
} 
 
/** 
 * _alaisb - mimics the alias builtin (man alias) 
 * @sd: Structure containing potential arguments. Used to maintain 
 *          constant function prototype. 
 *  Return: Always 0 
 */ 
int _alaisb(sd_t *sd) 
{ 
	int i = 0; 
	char *p = NULL; 
	list_t *node = NULL; 
 
	if (sd->argc == 1) 
	{ 
		node = sd->alias; 
		while (node) 
		{ 
			_palais(node); 
			node = node->next; 
		} 
		return (0); 
	} 
	for (i = 1; sd->argv[i]; i++) 
	{ 
		p = _charinsr(sd->argv[i], '='); 
		if (p) 
			_salais(sd, sd->argv[i]); 
		else 
			_palais(node_starts_with(sd->alias, sd->argv[i], '=')); 
	} 
 
	return (0); 
}
