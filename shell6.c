#include "shell.h" 
 
/** 
 * _csti - converts a string to an integer 
 * @s: the string to be converted 
 * Return: 0 if no numbers in string, converted number otherwise 
 *       -1 on error 
 */ 
int _csti(char *s) 
{ 
	int i = 0; 
	unsigned long int result = 0; 
 
	if (*s == '+') 
		s++;  /* TODO: why does this make main return 255? */ 
	for (i = 0;  s[i] != '\0'; i++) 
	{ 
		if (s[i] >= '0' && s[i] <= '9') 
		{ 
			result *= 10; 
			result += (s[i] - '0'); 
			if (result > INT_MAX) 
				return (-1); 
		} 
		else 
			return (-1); 
	} 
	return (result); 
} 
 
/** 
 * _perror - prints an error message 
 * @sd: the parameter & return sd struct 
 * @esr: string containing specified error type 
 * Return: 0 if no numbers in string, converted number otherwise 
 *        -1 on error 
 */ 
void _perror(sd_t *sd, char *esr) 
{ 
	_pins(sd->fname); 
	_pins(": "); 
	_pdecimal(sd->line_count, STDERR_FILENO); 
	_pins(": "); 
	_pins(sd->argv[0]); 
	_pins(": "); 
	_pins(esr); 
} 
 
/** 
 * _pdecimal - function prints a decimal (integer) number (base 10) 
 * @input: the input 
 * @fd: the filedescriptor to write to 
 * 
 * Return: number of characters printed 
 */ 
int _pdecimal(int input, int fd) 
{ 
	int (*__putchar)(char) = _putchar; 
	int i, count = 0; 
	unsigned int _abs_, current; 
 
	if (fd == STDERR_FILENO) 
		__putchar = _inchar; 
	if (input < 0) 
	{ 
		_abs_ = -input; 
		__putchar('-'); 
		count++; 
	} 
	else 
		_abs_ = input; 
	current = _abs_; 
	for (i = 1000000000; i > 1; i /= 10) 
	{ 
		if (_abs_ / i) 
		{ 
			__putchar('0' + current / i); 
			count++; 
		} 
		current %= i; 
	} 
	__putchar('0' + current); 
	count++; 
 
	return (count); 
} 
 
/** 
 * _cfunction - converter function, a clone of itoa 
 * @num: number 
 * @base: base 
 * @flags: argument flags 
 * 
 * Return: string 
 */ 
char *_cfunction(long int num, int base, int flags) 
{ 
	static char *array; 
	static char buffer[50]; 
	char sign = 0; 
	char *ptob; 
	unsigned long n = num; 
 
	if (!(flags & CONVERT_UNSIGNED) && num < 0) 
	{ 
		n = -num; 
		sign = '-'; 
 
	} 
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF"; 
	ptob = &buffer[49]; 
	*ptob = '\0'; 
 
	do	{ 
		*--ptob = array[n % base]; 
		n /= base; 
	} while (n != 0); 
 
	if (sign) 
		*--ptob = sign; 
	return (ptob); 
} 
 
/** 
 * rm_comments - function replaces first instance of '#' with '\0' 
 * @buf: address of the string to modify 
 * 
 * Return: Always 0; 
 */ 
void rm_comments(char *buf) 
{ 
	int i; 
 
	for (i = 0; buf[i] != '\0'; i++) 
		if (buf[i] == '#' && (!i || buf[i - 1] == ' ')) 
		{ 
			buf[i] = '\0'; 
			break; 
		} 
} 
