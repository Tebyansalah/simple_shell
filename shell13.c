#include "shell.h" 
 
/** 
 * pofree - frees a pointer and NULLs the address 
 * @ptob: address of the pointer to free 
 * 
 * Return: 1 if freed, otherwise 0. 
 */ 
int pofree(void **ptob) 
{ 
	if (ptob && *ptob) 
	{ 
		free(*ptob); 
		*ptob = NULL; 
		return (1); 
	} 
	return (0); 
}
