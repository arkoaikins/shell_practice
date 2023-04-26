#ifndef S_SHELL_H
#define S_SHELL_H

#define END_OF_FILE -2
#define EXIT -3

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>


/* Global environemnt */
extern char **environ;
/* Global program name */
char *name;
/* Global history counter */
int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin cmds.
 * @name: The name of the builtin cmd.
 * @f: A function pointer to the builtin cmd's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **top);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main Helpers */
ssize_t line_gets(char **linepnt, size_t *n, FILE *strm);
void *re_alloc(void *pnt, unsigned int size1, unsigned int size2);
char **strtoken(char *line, char *dlim);
char *locate(char *cmd);
list_t *ret_dir(char *path);
int perform(char **agt, char **top);
void _releasing(list_t *head);
char *_attol(int num);

/* Input Helpers */
void handle_line(char **line, ssize_t read);
void _replacer(char **agt, int *impret);
char *get_agt(char *line, int *impret);
int call_agt(char **agt, char **top, int *impret);
int run_agt(char **agt, char **top, int *impret);
int handle_agt(int *impret);
int check_agt(char **agt);
void free_agt(char **agt, char **top);
int prog_commd(char *file_path, int *impret);
char **change_aliases(char **agt);

/* String functions */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*get_builtin(char *cmd))(char **agt, char **top);
int by_exit(char **agt, char **top);
int by_env(char **agt, char __attribute__((__unused__)) **top);
int by_set(char **agt, char __attribute__((__unused__)) **top);
int by_unset(char **agt, char __attribute__((__unused__)) **top);
int by_cd(char **agt, char __attribute__((__unused__)) **top);
int by_alias(char **agt, char __attribute__((__unused__)) **top);
int by_help(char **agt, char __attribute__((__unused__)) **top);

/* Builtin Helpers */
char **env_copy(void);
void free_env(void);
char **env_get(const char *var);

/* Error Handling */
int do_error(char **agt, int err);
char *environ_error(char **agt);
char *error_1(char **agt);
char *error_2_exit(char **agt);
char *error_2_cd(char **agt);
char *error_2_syntax(char **agt);
char *error_126(char **agt);
char *error_127(char **agt);

/* Linkedlist Helpers */
alias_t *alias_adder(alias_t **head, char *name, char *value);
void release_alias_l(alias_t *head);
list_t *node_adder(list_t **head, char *dir);
void _releasing(list_t *head);

void overall_helper(void);
void alias_helper(void);
void cd_helper(void);
void exit_helper(void);
void wa_wa(void);
void env_helper(void);
void setenv_hepler_1(void);
void unset_helper(void);
void ance_helper(void);

#endif
