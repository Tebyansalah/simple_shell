#include "shell.h" 
 
/** 
 * _ex - exits the shell 
 * @sd: Structure containing potential arguments. Used to maintain 
 *          constant function prototype. 
 *  Return: exits with a given exit status 
 *         (0) if sd.argv[0] != "exit" 
 */ 
int _ex(sd_t *sd) 
{ 
	int exitcheck; 
 
	if (sd->argv[1])  /* If there is an exit arguement */ 
	{ 
		exitcheck = _csti(sd->argv[1]); 
		if (exitcheck == -1) 
		{ 
			sd->status = 2; 
			_perror(sd, "Illegal number: "); 
			_pins(sd->argv[1]); 
			_inchar('\n'); 
			return (1); 
		} 
		sd->err_num = _csti(sd->argv[1]); 
		return (-2); 
	} 
	sd->err_num = -1; 
	return (-2); 
} 
 
/** 
 *_cd - changes the current directory of the process 
 * @sd: Structure containing potential arguments. Used to maintain 
 *          constant function prototype. 
 *  Return: Always 0 
 */ 
int_cd(sd_t *sd) 
{ 
	char *s, *dir, buffer[1024]; 
	int chdir_ret; 
 
	s = getcwd(buffer, 1024); 
	if (!s) 
		_puts("TODO: >>getcwd failure emsg here<<\n"); 
	if (!sd->argv[1]) 
	{ 
		dir = _envalue(sd, "HOME="); 
		if (!dir) 
			chdir_ret = /* TODO: what should this be? */ 
				chdir((dir = _envalue(sd, "PWD=")) ? dir : "/"); 
		else 
			chdir_ret = chdir(dir); 
	} 
	else if (_towstr(sd->argv[1], "-") == 0) 
	{ 
		if (!_envalue(sd, "OLDPWD=")) 
		{ 
			_puts(s); 
			_putchar('\n'); 
			return (1); 
		} 
		_puts(_envalue(sd, "OLDPWD=")), _putchar('\n'); 
		chdir_ret = /* TODO: what should this be? */ 
			chdir((dir = _envalue(sd, "OLDPWD=")) ? dir : "/"); 
	} 
	else 
		chdir_ret = chdir(sd->argv[1]); 
	if (chdir_ret == -1) 
	{ 
		_perror(sd, "can't cd to "); 
		_pins(sd->argv[1]), _inchar('\n'); 
	} 
	else 
	{ 
		_newenvi(sd, "OLDPWD", _envalue(sd, "PWD=")); 
		_newenvi(sd, "PWD", getcwd(buffer, 1024)); 
	} 
	return (0); 
} 
 
/** 
 * _ghcd - changes the current directory of the process 
 * @sd: Structure containing potential arguments. Used to maintain 
 *          constant function prototype. 
 *  Return: Always 0 
 */ 
int _ghcd(sd_t *sd) 
{ 
	char **arg_array; 
 
	arg_array = sd->argv; 
	_puts("help call works. Function not yet implemented \n"); 
	if (0) 
		_puts(*arg_array); /* temp att_unused workaround */ 
	return (0); 
}
