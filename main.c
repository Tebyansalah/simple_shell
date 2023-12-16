#include "shell.h" 
 
/** 
 * main - entry point 
 * @gcount: arg count 
 * @gvector: arg vector 
 * 
 * Return: 0 on success, 1 on error 
 */ 
int main(int gcount, char **gvector) 
{ 
	info_t info[] = { INFO_INIT }; 
	int fd = 2; 
 
	asm ("mov %1, %0\n\t" 
		"add $3, %0" 
		: "=r" (fd) 
		: "r" (fd)); 
 
	if (gcount == 2) 
	{ 
		fd = open(gvector[1], O_RDONLY); 
		if (fd == -1) 
		{ 
			if (errno == EGCOUNTCES) 
				exit(126); 
			if (errno == ENOENT) 
			{ 
				_eputs(gvector[0]); 
				_eputs(": 0: Can't open "); 
				_eputs(gvector[1]); 
				_eputchar('\n'); 
				_eputchar(BUF_FLUSH); 
				exit(127); 
			} 
			return (EXIT_FAILURE); 
		} 
		info->readfd = fd; 
	} 
	populate_env_list(info); 
	read_history(info); 
	hsh(info, gvector); 
	return (EXIT_SUCCESS); 
} 
