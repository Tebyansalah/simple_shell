#include "shell.h" 
 
/** 
 **_memory - fills memory with a constant byte 
 *@s: the pointer to the memory area 
 *@b: the byte to fill *s with 
 *@n: the amount of bytes to be filled 
 *Return: (s) a pointer to the memory area s 
 */ 
char *_memory(char *s, char b, unsigned int n) 
{ 
	unsigned int i; 
 
	for (i = 0; i < n; i++) 
		s[i] = b; 
	return (s); 
} 
 
/** 
 * ffree - frees a string of strings 
 * @pp: string of strings 
 */ 
void ffree(char **pp) 
{ 
	char **a = pp; 
 
	if (!pp) 
		return; 
	while (*pp) 
		free(*pp++); 
	free(a); 
} 
 
/** 
 * _reloblock - reallocates a block of memory 
 * @ptob: pointer to previous malloc'ated block 
 * @os: byte size of previous block 
 * @ns: byte size of new block 
 * 
 * Return: pointer to da ol'block nameen. 
 */ 
void *_reloblock(void *ptob, unsigned int os, unsigned int ns) 
{ 
	char *p; 
 
	if (!ptob) 
		return (malloc(ns)); 
	if (!ns) 
		return (free(ptob), NULL); 
	if (ns == os) 
		return (ptob); 
 
	p = malloc(ns); 
	if (!p) 
		return (NULL); 
 
	os = os < ns ? os : ns; 
	while (os--) 
		p[os] = ((char *)ptob)[os]; 
	free(ptob); 
	return (p); 
}
