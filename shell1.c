#include "shell.h" 
 
/** 
 * inactive - returns true if shell is interactive mode 
 * @sd: struct address 
 * 
 * Return: 1 if interactive mode, 0 otherwise 
 */ 
int inactive(sd_t *sd) 
{ 
	return (isatty(STDIN_FILENO) && sd->readfd <= 2); 
} 
 
/** 
 * _dm - checks if character is a delimeter 
 * @c: the char to check 
 * @delim: the delimeter string 
 * Return: 1 if true, 0 if false 
 */ 
int _dm(char c, char *delim) 
{ 
	while (*delim) 
		if (*delim++ == c) 
			return (1); 
	return (0); 
} 
 
/** 
 *_alph - checks for alphabetic character 
 *@c: The character to input 
 *Return: 1 if c is alphabetic, 0 otherwise 
 */ 
 
int _alph(int c) 
{ 
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) 
		return (1); 
	else 
		return (0); 
} 
 
/** 
 *_sti - converts a string to an integer 
 *@s: the string to be converted 
 *Return: 0 if no numbers in string, converted number otherwise 
 */ 
 
int _sti(char *s) 
{ 
	int i, sign = 1, flag = 0, output; 
	unsigned int result = 0; 
 
	for (i = 0;  s[i] != '\0' && flag != 2; i++) 
	{ 
		if (s[i] == '-') 
			sign *= -1; 
 
		if (s[i] >= '0' && s[i] <= '9') 
		{ 
			flag = 1; 
			result *= 10; 
			result += (s[i] - '0'); 
		} 
		else if (flag == 1) 
			flag = 2; 
	} 
 
	if (sign == -1) 
		output = -result; 
	else 
		output = result; 
 
	return (output); 
} 
