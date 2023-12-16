#include "shell.h" 
 
/** 
 **_copystr - copies a string 
 *@dstc: the destination string to be copied to 
 *@susr: the source string 
 *@n: the amount of characters to be copied 
 *Return: the concatenated string 
 */ 
char *_copystr(char *dstc, char *susr, int n) 
{ 
	int i, j; 
	char *s = dstc; 
 
	i = 0; 
	while (susr[i] != '\0' && i < n - 1) 
	{ 
		dstc[i] = susr[i]; 
		i++; 
	} 
	if (i < n) 
	{ 
		j = i; 
		while (j < n) 
		{ 
			dstc[j] = '\0'; 
			j++; 
		} 
	} 
	return (s); 
} 
 
/** 
 **_towsr - concatenates two strings 
 *@dstc: the first string 
 *@susr: the second string 
 *@n: the amount of bytes to be maximally used 
 *Return: the concatenated string 
 */ 
char *_towsr(char *dstc, char *susr, int n) 
{ 
	int i, j; 
	char *s = dstc; 
 
	i = 0; 
	j = 0; 
	while (dstc[i] != '\0') 
		i++; 
	while (susr[j] != '\0' && j < n) 
	{ 
		dstc[i] = susr[j]; 
		i++; 
		j++; 
	} 
	if (j < n) 
		dstc[i] = '\0'; 
	return (s); 
} 
 
/** 
 **_charinsr - locates a character in a string 
 *@s: the string to be parsed 
 *@c: the character to look for 
 *Return: (s) a pointer to the memory area s 
 */ 
char *_charinsr(char *s, char c) 
{ 
	do { 
		if (*s == c) 
			return (s); 
	} while (*s++ != '\0'); 
 
	return (NULL); 
}
