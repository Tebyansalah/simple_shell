#include "shell.h" 
 
/** 
 * int_sd - initializes sd_t struct 
 * @sd: struct address 
 */ 
void int_sd(sd_t *sd) 
{ 
	sd->arg = NULL; 
	sd->argv = NULL; 
	sd->path = NULL; 
	sd->argc = 0; 
} 
 
/** 
 * put_sd - initializes sd_t struct 
 * @sd: struct address 
 * @rvct: argument vector 
 */ 
void put_sd(sd_t *sd, char **rvct) 
{ 
	int i = 0; 
 
	sd->fname = rvct[0]; 
	if (sd->arg) 
	{ 
		sd->argv = strtow(sd->arg, " \t"); 
		if (!sd->argv) 
		{ 
 
			sd->argv = malloc(sizeof(char *) * 2); 
			if (sd->argv) 
			{ 
				sd->argv[0] = _strdup(sd->arg); 
				sd->argv[1] = NULL; 
			} 
		} 
		for (i = 0; sd->argv && sd->argv[i]; i++) 
			; 
		sd->argc = i; 
 
		rep_tokenalias(sd); 
		replace_vars(sd); 
	} 
} 
 
/** 
 * _freesd - frees sd_t struct fields 
 * @sd: struct address 
 * @all: true if freeing all fields 
 */ 
void _freesd(sd_t *sd, int all) 
{ 
	ffree(sd->argv); 
	sd->argv = NULL; 
	sd->path = NULL; 
	if (all) 
	{ 
		if (!sd->cmd_buf) 
			free(sd->arg); 
		if (sd->env) 
			free_list(&(sd->env)); 
		if (sd->history) 
			free_list(&(sd->history)); 
		if (sd->alias) 
			free_list(&(sd->alias)); 
		ffree(sd->environ); 
			sd->environ = NULL; 
		pofree((void **)sd->cmd_buf); 
		if (sd->readfd > 2) 
			close(sd->readfd); 
		_putchar(BUF_FLUSH); 
	} 
}
