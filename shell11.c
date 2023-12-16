#include "shell.h" 
 
/** 
 * his_file - gets the history file 
 * @sd: parameter struct 
 * 
 * Return: allocated string containg history file 
 */ 
 
char *his_file(sd_t *sd) 
{ 
	char *buf, *dir; 
 
	dir = _envalue(sd, "HOME="); 
	if (!dir) 
		return (NULL); 
	buf = malloc(sizeof(char) * (_lengstr(dir) + _lengstr(HIST_FILE) + 2)); 
	if (!buf) 
		return (NULL); 
	buf[0] = 0; 
	_strcpy(buf, dir); 
	_strcat(buf, "/"); 
	_strcat(buf, HIST_FILE); 
	return (buf); 
} 
 
/** 
 * wr_his - creates a file, or appends to an existing file 
 * @sd: the parameter struct 
 * 
 * Return: 1 on success, else -1 
 */ 
int wr_his(sd_t *sd) 
{ 
	ssize_t fd; 
	char *filename = his_file(sd); 
	list_t *node = NULL; 
 
	if (!filename) 
		return (-1); 
 
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644); 
	free(filename); 
	if (fd == -1) 
		return (-1); 
	for (node = sd->history; node; node = node->next) 
	{ 
		_pinst(node->sr, fd); 
		_charfd('\n', fd); 
	} 
	_charfd(BUF_FLUSH, fd); 
	close(fd); 
	return (1); 
} 
 
/** 
 * r_his - reads history from file 
 * @sd: the parameter struct 
 * 
 * Return: histcount on success, 0 otherwise 
 */ 
int r_his(sd_t *sd) 
{ 
	int i, last = 0, linecount = 0; 
	ssize_t fd, rdlen, fsize = 0; 
	struct stat st; 
	char *buf = NULL, *filename = his_file(sd); 
 
	if (!filename) 
		return (0); 
 
	fd = open(filename, O_RDONLY); 
	free(filename); 
	if (fd == -1) 
		return (0); 
	if (!fstat(fd, &st)) 
		fsize = st.st_size; 
	if (fsize < 2) 
		return (0); 
	buf = malloc(sizeof(char) * (fsize + 1)); 
	if (!buf) 
		return (0); 
	rdlen = read(fd, buf, fsize); 
	buf[fsize] = 0; 
	if (rdlen <= 0) 
		return (free(buf), 0); 
	close(fd); 
	for (i = 0; i < fsize; i++) 
		if (buf[i] == '\n') 
		{ 
			buf[i] = 0; 
			add_entry_his(sd, buf + last, linecount++); 
			last = i + 1; 
		} 
	if (last != i) 
		add_entry_his(sd, buf + last, linecount++); 
	free(buf); 
	sd->histcount = linecount; 
	while (sd->histcount-- >= HIST_MAX) 
		delete_node_at_index(&(sd->history), 0); 
	re_num_his(sd); 
	return (sd->histcount); 
} 
 
/** 
 * add_entry_his - adds entry to a history linked list 
 * @sd: Structure containing potential arguments. Used to maintain 
 * @buf: buffer 
 * @linecount: the history linecount, histcount 
 * 
 * Return: Always 0 
 */ 
int add_entry_his(sd_t *sd, char *buf, int linecount) 
{ 
	list_t *node = NULL; 
 
	if (sd->history) 
		node = sd->history; 
	add_node_end(&node, buf, linecount); 
 
	if (!sd->history) 
		sd->history = node; 
	return (0); 
} 
 
/** 
 * re_num_his - renumbers the history linked list after changes 
 * @sd: Structure containing potential arguments. Used to maintain 
 * 
 * Return: the new histcount 
 */ 
int re_num_his(sd_t *sd) 
{ 
	list_t *node = sd->history; 
	int i = 0; 
 
	while (node) 
	{ 
		node->num = i++; 
		node = node->next; 
	} 
	return (sd->histcount = i); 
} 
