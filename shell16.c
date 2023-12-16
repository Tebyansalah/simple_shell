#include "shell.h" 
 
/** 
 * shloop - main shell loop 
 * @sd: the parameter & return sd struct 
 * @rvct: the argument vector from main() 
 * 
 * Return: 0 on success, 1 on error, or error code 
 */ 
int shloop(sd_t *sd, char **rvct) 
{ 
	ssize_t r = 0; 
	int builtin_ret = 0; 
 
	while (r != -1 && builtin_ret != -2) 
	{ 
		int_sd(sd); 
		if (inactive(sd)) 
			_puts("$ "); 
		_inchar(BUF_FLUSH); 
		r = new_line(sd); 
		if (r != -1) 
		{ 
			put_sd(sd, rvct); 
			builtin_ret = buil_comm(sd); 
			if (builtin_ret == -1) 
				comm_path(sd); 
		} 
		else if (inactive(sd)) 
			_putchar('\n'); 
		_freesd(sd, 0); 
	} 
	wr_his(sd); 
	_freesd(sd, 1); 
	if (!inactive(sd) && sd->status) 
		exit(sd->status); 
	if (builtin_ret == -2) 
	{ 
		if (sd->err_num == -1) 
			exit(sd->status); 
		exit(sd->err_num); 
	} 
	return (builtin_ret); 
} 
 
/** 
 * buil_comm - finds a builtin command 
 * @sd: the parameter & return sd struct 
 * 
 * Return: -1 if builtin not found, 
 *			0 if builtin executed successfully, 
 *			1 if builtin found but not successful, 
 *			-2 if builtin signals exit() 
 */ 
int buil_comm(sd_t *sd) 
{ 
	int i, built_in_ret = -1; 
	builtin_table builtintbl[] = { 
		{"exit", _ex}, 
		{"env", _envi}, 
		{"help", _ghcd}, 
		{"history", _hslist}, 
		{"setenv", _newenv}, 
		{"unsetenv", _rmenv}, 
		{"cd",_cd}, 
		{"alias", _alaisb}, 
		{NULL, NULL} 
	}; 
 
	for (i = 0; builtintbl[i].type; i++) 
		if (_towstr(sd->argv[0], builtintbl[i].type) == 0) 
		{ 
			sd->line_count++; 
			built_in_ret = builtintbl[i].func(sd); 
			break; 
		} 
	return (built_in_ret); 
} 
 
/** 
 * comm_path - finds a command in PATH 
 * @sd: the parameter & return sd struct 
 * 
 * Return: void 
 */ 
void comm_path(sd_t *sd) 
{ 
	char *path = NULL; 
	int i, k; 
 
	sd->path = sd->argv[0]; 
	if (sd->linecount_flag == 1) 
	{ 
		sd->line_count++; 
		sd->linecount_flag = 0; 
	} 
	for (i = 0, k = 0; sd->arg[i]; i++) 
		if (!_dm(sd->arg[i], " \t\n")) 
			k++; 
	if (!k) 
		return; 
 
	path = _paths(sd, _envalue(sd, "PATH="), sd->argv[0]); 
	if (path) 
	{ 
		sd->path = path; 
		run_cmd(sd); 
	} 
	else 
	{ 
		if ((inactive(sd) || _envalue(sd, "PATH=") 
			|| sd->argv[0][0] == '/') && ex_com(sd, sd->argv[0])) 
			run_cmd(sd); 
		else if (*(sd->arg) != '\n') 
		{ 
			sd->status = 127; 
			_perror(sd, "not found\n"); 
		} 
	} 
} 
 
/** 
 * run_cmd - forks a an exec thread to run cmd 
 * @sd: the parameter & return sd struct 
 * 
 * Return: void 
 */ 
void run_cmd(sd_t *sd) 
{ 
	pid_t child_pid; 
 
	child_pid = fork(); 
	if (child_pid == -1) 
	{ 
		/* TODO: PUT ERROR FUNCTION */ 
		perror("Error:"); 
		return; 
	} 
	if (child_pid == 0) 
	{ 
		if (execve(sd->path, sd->argv, re_environ (sd)) == -1) 
		{ 
			_freesd(sd, 1); 
			if (errno == EACCES) 
				exit(126); 
			exit(1); 
		} 
		/* TODO: PUT ERROR FUNCTION */ 
	} 
	else 
	{ 
		wait(&(sd->status)); 
		if (WIFEXITED(sd->status)) 
		{ 
			sd->status = WEXITSTATUS(sd->status); 
			if (sd->status == 126) 
				_perror(sd, "Permission denied\n"); 
		} 
	} 
} 
