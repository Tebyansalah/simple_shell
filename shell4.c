#include "shell.h" 
 
/** 
 * _envi - prints the current environment 
 * @sd: Structure containing potential arguments. Used to maintain 
 *          constant function prototype. 
 * Return: Always 0 
 */ 
int _envi(sd_t *sd) 
{ 
	p_list_sr(sd->env); 
	return (0); 
} 
 
/** 
 * _envalue - gets the value of an environ variable 
 * @sd: Structure containing potential arguments. Used to maintain 
 * @name: env var name 
 * 
 * Return: the value 
 */ 
char *_envalue(sd_t *sd, const char *name) 
{ 
	list_t *node = sd->env; 
	char *p; 
 
	while (node) 
	{ 
		p = starts_with(node->sr, name); 
		if (p && *p) 
			return (p); 
		node = node->next; 
	} 
	return (NULL); 
} 
 
/** 
 * _newenv - Initialize a new environment variable, 
 *             or modify an existing one 
 * @sd: Structure containing potential arguments. Used to maintain 
 *        constant function prototype. 
 *  Return: Always 0 
 */ 
int _newenv(sd_t *sd) 
{ 
	if (sd->argc != 3) 
	{ 
		_pins("Incorrect number of arguements\n"); 
		return (1); 
	} 
	if (_newenvi(sd, sd->argv[1], sd->argv[2])) 
		return (0); 
	return (1); 
} 
 
/** 
 * _rmenv - Remove an environment variable 
 * @sd: Structure containing potential arguments. Used to maintain 
 *        constant function prototype. 
 *  Return: Always 0 
 */ 
int _rmenv(sd_t *sd) 
{ 
	int i; 
 
	if (sd->argc == 1) 
	{ 
		_pins("Too few arguements.\n"); 
		return (1); 
	} 
	for (i = 1; i <= sd->argc; i++) 
		_rmenviv(sd, sd->argv[i]); 
 
	return (0); 
} 
 
/** 
 * _envlink - populates env linked list 
 * @sd: Structure containing potential arguments. Used to maintain 
 *          constant function prototype. 
 * Return: Always 0 
 */ 
int _envlink(sd_t *sd) 
{ 
	list_t *node = NULL; 
	size_t i; 
 
	for (i = 0; environ[i]; i++) 
		add_node_end(&node, environ[i], 0); 
	sd->env = node; 
	return (0); 
}
