#include "shell.h" 
 
/** 
 * in_buff - buffers chained commands 
 * @sd: parameter struct 
 * @buf: address of buffer 
 * @len: address of len var 
 * 
 * Return: bytes read 
 */ 
ssize_t in_buff(sd_t *sd, char **buf, size_t *len) 
{ 
	ssize_t r = 0; 
	size_t len_p = 0; 
 
	if (!*len) /* if nothing left in the buffer, fill it */ 
	{ 
		/*pofree((void **)sd->cmd_buf);*/ 
		free(*buf); 
		*buf = NULL; 
		signal(SIGINT, shan); 
#if USE_NEXTLINE 
		r = getline(buf, &len_p, stdin); 
#else 
		r = _nextline(sd, buf, &len_p); 
#endif 
		if (r > 0) 
		{ 
			if ((*buf)[r - 1] == '\n') 
			{ 
				(*buf)[r - 1] = '\0'; /* remove trailing newline */ 
				r--; 
			} 
			sd->linecount_flag = 1; 
			rm_comments(*buf); 
			add_entry_his(sd, *buf, sd->histcount++); 
			/* if (_charinsr(*buf, ';')) is this a command chain? */ 
			{ 
				*len = r; 
				sd->cmd_buf = buf; 
			} 
		} 
	} 
	return (r); 
} 
 
/** 
 * new_line - gets a line minus the newline 
 * @sd: parameter struct 
 * 
 * Return: bytes read 
 */ 
ssize_t new_line(sd_t *sd) 
{ 
	static char *buf; /* the ';' command chain buffer */ 
	static size_t i, j, len; 
	ssize_t r = 0; 
	char **buf_p = &(sd->arg), *p; 
 
	_putchar(BUF_FLUSH); 
	r = in_buff(sd, &buf, &len); 
	if (r == -1) /* EOF */ 
		return (-1); 
	if (len)	/* we have commands left in the chain buffer */ 
	{ 
		j = i; /* init new iterator to current buf position */ 
		p = buf + i; /* get pointer for return */ 
 
		chain_stat(sd, buf, &j, i, len); 
		while (j < len) 		{ 
			if (chain_dem(sd, buf, &j)) 
				break; 
			j++; 
		} 
 
		i = j + 1;  

		if (i >= len)  
		{ 
			i = len = 0;  
			sd->cmd_buf_type = CMD_NORM; 
		} 
 
		*buf_p = p; /* pass back pointer to current command position */ 
		return (_lengstr(p)); /* return length of current command */ 
	} 
 
	*buf_p = buf; /* else not a chain, pass back buffer from _nextline() */ 
	return (r); /* return length of buffer from _nextline() */ 
} 
 
/** 
 * r_buff - reads a buffer 
 * @sd: parameter struct 
 * @buf: buffer 
 * @i: size 
 * 
 * Return: r 
 */ 
ssize_t r_buff(sd_t *sd, char *buf, size_t *i) 
{ 
	ssize_t r = 0; 
 
	if (*i) 
		return (0); 
	r = read(sd->readfd, buf, R_BUFF_SIZE); 
	if (r >= 0) 
		*i = r; 
	return (r); 
} 
 
/** 
 * _nextline - gets the next line of input from STDIN 
 * @sd: parameter struct 
 * @ptob: address of pointer to buffer, preallocated or NULL 
 * @length: size of preallocated ptob buffer if not NULL 
 * 
 * Return: s 
 */ 
int _nextline(sd_t *sd, char **ptob, size_t *length) 
{ 
	static char buf[R_BUFF_SIZE]; 
	static size_t i, len; 
	size_t k; 
	ssize_t r = 0, s = 0; 
	char *p = NULL, *new_p = NULL, *c; 
 
	p = *ptob; 
	if (p && length) 
		s = *length; 
	if (i == len) 
		i = len = 0; 
 
	r = r_buff(sd, buf, &len); 
	if (r == -1 || (r == 0 && len == 0)) 
		return (-1); 
 
	c = _charinsr(buf + i, '\n'); 
	k = c ? 1 + (unsigned int)(c - buf) : len; 
	new_p = _reloblock(p, s, s ? s + k : k + 1); 
	if (!new_p) /* MALLOC FAILURE! */ 
		return (p ? free(p), -1 : -1); 
 
	if (s) 
		_towsr(new_p, buf + i, k - i); 
	else 
		_copystr(new_p, buf + i, k - i + 1); 
 
	s += k - i; 
	i = k; 
	p = new_p; 
 
	if (length) 
		*length = s; 
	*ptob = p; 
	return (s); 
} 
 
/** 
 * shan - blocks ctrl-C 
 * @sig_num: the signal number 
 * 
 * Return: void 
 */ 
void shan(__attribute__((unused))int sig_num) 
{ 
	_puts("\n"); 
	_puts("$ "); 
	_putchar(BUF_FLUSH); 
}
