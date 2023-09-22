#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* this is for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* this is for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* this is for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* prototyps_shloop.c */
int sh(info_t *, char **);
int f_built(info_t *);
void f_cm(info_t *);
void fk_cm(info_t *);

/* prototyps_parser.c */
int hello_cmd(info_t *, char *);
char *dupli_charss(char *, int, int);
char *catch_pat(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* prototyps_errors.c */
void print_str(char *);
int write_char(char);
int write_fd(char c, int fd);
int puts_fde(char *str, int fd);

/* prototyps_string.c */
int len_str(char *);
int cmp_str(char *, char *);
char *push_hard(const char *, const char *);
char *cat_str(char *, char *);

/* prototyps_string1.c */
char *cpy_stri(char *, char *);
char *dupli_sat(const char *);
void _puts(char *);
int _putchar(char);

/* prototyps_exits.c */
char *copy_string(char *, char *, int);
char *concat_str(char *, char *, int);
char *char_str(char *, char);

/* prototyps_tokenizer.c */
char **split_str(char *, char *);
char **split_str2(char *, char);

/* prototyps_realloc.c */
char *_senna(char *, char, unsigned int);
void vladimer(char **);
void *re_allo(void *, unsigned int, unsigned int);

/* prototyps_memory.c */
int fr(void **);

/*prototyps a_toi.c */
int inter_act(info_t *info);
int is_that_deli(char, char *);
int is_alpha(int);
int a_toi(char *);

/* prototyps_errors1.c */
int err(char *);
void printerr(info_t *, char *);
int printdec(int, int);
char *convnum(long int, int, int);
void remcomm(char *);

/* prototyps_builtin.c */
int my_exit(info_t *);
int my_cd(info_t *);
int my_help(info_t *);

/* prototyps_builtin1.c */
int my_date(info_t *);
int alias_mine(info_t *);

/*prototyps_getline.c */
ssize_t _youmi(info_t *);
int get_linee(info_t *, char **, size_t *);
void zed_assian(int);

/* prototyps_getinfo.c */
void clinformation(info_t *);
void s_information(info_t *, char **);
void frinformation(info_t *, int);

/* prototyps_environ.c */
char *get_enviro(info_t *, const char *);
int my_enviro(info_t *);
int my_set_env(info_t *);
int my_unset_env(info_t *);
int pop_envlist(info_t *);

/* prototyps_getenv.c */
char **catch_env(info_t *);
int jax_str(info_t *, char *);
int seraphine_str(info_t *, char *, char *);

/* prototyps_history.c */
char *pring_histroy_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* prototyps_lists.c */
list_t *insert_node(list_t **, const char *, int);
list_t *add_nody_end(list_t **, const char *, int);
size_t type_strlist(const list_t *);
int del_nody_atindex(list_t **, unsigned int);
void release_lis(list_t **);

/* prototyps_lists1.c */
size_t listlength(const list_t *);
char **listrings(list_t *);
size_t pri_li(const list_t *);
list_t *n_start(list_t *, char *, char);
ssize_t gt_index(list_t *, list_t *);

/* prototyps_vars.c */
int chain(info_t *, char *, size_t *);
void ch_ch(info_t *, char *, size_t *, size_t, size_t);
int rep_ali(info_t *);
int rep_var(info_t *);
int rep_str(char **, char *);

#endif
