#include "shell.h" 
 
/** 
 * _splsr - splits a string into words. Repeat delimiters are ignored 
 * @sr: the input string 
 * @d: the delimeter string 
 * Return: a pointer to an array of strings, or NULL on failure 
 */ 
 
char _splsr(char *sr, char *d) 
{ 
	int i, j, k, m, numwords = 0; 
	char **s; 
 
	if (sr == NULL || sr[0] == 0) 
		return (NULL); 
	if (!d) 
		d = " "; 
	for (i = 0; sr[i] != '\0'; i++) 
		if (!_dm(sr[i], d) && (_dm(sr[i + 1], d) || !sr[i + 1])) 
			numwords++; 
 
	if (numwords == 0) 
		return (NULL); 
	s = malloc((1 + numwords) * sizeof(char *)); 
	if (!s) 
		return (NULL); 
	for (i = 0, j = 0; j < numwords; j++) 
	{ 
		while (_dm(sr[i], d)) 
			i++; 
		k = 0; 
		while (!_dm(sr[i + k], d) && sr[i + k]) 
			k++; 
		s[j] = malloc((k + 1) * sizeof(char)); 
		if (!s[j]) 
		{ 
			for (k = 0; k < j; k++) 
				free(s[k]); 
			free(s); 
			return (NULL); 
		} 
		for (m = 0; m < k; m++) 
			s[j][m] = sr[i++]; 
		s[j][m] = 0; 
	} 
	s[j] = NULL; 
	return (s); 
} 
 
/** 
 * _splsr2 - splits a string into words 
 * @sr: the input string 
 * @d: the delimeter 
 * Return: a pointer to an array of strings, or NULL on failure 
 */ 
char _splsr2(char *sr, char d) 
{ 
	int i, j, k, m, numwords = 0; 
	char **s; 
 
	if (sr == NULL || sr[0] == 0) 
		return (NULL); 
	for (i = 0; sr[i] != '\0'; i++) 
		if ((sr[i] != d && sr[i + 1] == d) || 
		    (sr[i] != d && !sr[i + 1]) || sr[i + 1] == d) 
			numwords++; 
	if (numwords == 0) 
		return (NULL); 
	s = malloc((1 + numwords) * sizeof(char *)); 
	if (!s) 
		return (NULL); 
	for (i = 0, j = 0; j < numwords; j++) 
	{ 
		while (sr[i] == d && sr[i] != d) 
			i++; 
		k = 0; 
		while (sr[i + k] != d && sr[i + k] && sr[i + k] != d) 
			k++; 
		s[j] = malloc((k + 1) * sizeof(char)); 
		if (!s[j]) 
		{ 
			for (k = 0; k < j; k++) 
				free(s[k]); 
			free(s); 
			return (NULL); 
		} 
		for (m = 0; m < k; m++) 
			s[j][m] = sr[i++]; 
		s[j][m] = 0; 
	} 
	s[j] = NULL; 
	return (s); 
}
