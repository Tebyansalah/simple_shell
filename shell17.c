#include "shell.h" 
 
/** 
 * _lengstr - returns the length of a string 
 * @s: the string whose length to check 
 * 
 * Return: integer length of string 
 */ 
int _lengstr(char *s) 
{ 
	int i = 0; 
 
	if (!s) 
		return (0); 
 
	while (*s++) 
		i++; 
	return (i); 
} 
 
/** 
 * _towstr - performs lexicogarphic comparison of two strangs. 
 * @fs: the first strang 
 * @s2: the second strang 
 * 
 * Return: negative if fs < cs, positive if fs > cs, zero if fs == cs 
 */ 
int _towstr(char *fs, char *cs) 
{ 
	while (*fs && *cs) 
	{ 
		if (*fs != *cs) 
			return (*fs - *s2); 
		fs++; 
		s2++; 
	} 
	if (*fs == *s2) 
		return (0); 
	else 
		return (*fs < *s2 ? -1 : 1); 
} 
 
/** 
 * starts_with - checks if needle starts with haystack 
 * @haystack: string to search 
 * @needle: the substring to find 
 * 
 * Return: address of next char of haystack or NULL 
 */ 
char *starts_with(const char *haystack, const char *needle) 
{ 
	while (*needle) 
		if (*needle++ != *haystack++) 
			return (NULL); 
	return ((char *)haystack); 
} 
 
/** 
 * _strcat - concatenates two strings 
 * @dstc: the destination buffer 
 * @susr: the source buffer 
 * 
 * Return: pointer to destination buffer 
 */ 
char *_strcat(char *dstc, char *susr) 
{ 
	char *ret = dstc; 
 
	while (*dstc) 
		dstc++; 
	while (*susr) 
		*dstc++ = *susr++; 
	*dstc = *susr; 
	return (ret); 
}
