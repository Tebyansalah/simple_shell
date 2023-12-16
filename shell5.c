#include "shell.h" 
 
/** 
 *_pins - prints an input string 
 * @sr: the string to be printed 
 * 
 * Return: Nothing 
 */ 
void _pins(char *sr) 
{ 
	int i = 0; 
 
	if (!sr) 
		return; 
	while (sr[i] != '\0') 
	{ 
		_inchar(sr[i]); 
		i++; 
	} 
} 
 
/** 
 * _inchar - writes the character c to stderr 
 * @c: The character to print 
 * 
 * Return: On success 1. 
 * On error, -1 is returned, and errno is set appropriately. 
 */ 
int _inchar(char c) 
{ 
	static int i; 
	static char buf[WRITE_BUF_SIZE]; 
 
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) 
	{ 
		write(2, buf, i); 
		i = 0; 
	} 
	if (c != BUF_FLUSH) 
		buf[i++] = c; 
	return (1); 
} 
 
/** 
 * _charfd - writes the character c to given fd 
 * @c: The character to print 
 * @fd: The filedescriptor to write to 
 * 
 * Return: On success 1. 
 * On error, -1 is returned, and errno is set appropriately. 
 */ 
int _charfd(char c, int fd) 
{ 
	static int i; 
	static char buf[WRITE_BUF_SIZE]; 
 
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) 
	{ 
		write(fd, buf, i); 
		i = 0; 
	} 
	if (c != BUF_FLUSH) 
		buf[i++] = c; 
	return (1); 
} 
 
/** 
 *_pinst - prints an input string 
 * @sr: the string to be printed 
 * @fd: the filedescriptor to write to 
 * 
 * Return: the number of chars put 
 */ 
int _pinst(char *sr, int fd) 
{ 
	int i = 0; 
 
	if (!sr) 
		return (0); 
	while (*sr) 
	{ 
		i += _charfd(*sr++, fd); 
	} 
	return (i); 
}
