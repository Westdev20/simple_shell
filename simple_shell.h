#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

int free_pointer(void **ptr);
char *duplicate_char(char *pstr, int begin, int stop);
char *find_cmd_path(info_t *info, char *pstr, char *cmd);
int exe_cmd(info_t *info, char *p);
int main(int ac, char **av);
char *_memset(char *s, char b, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int alpha_char(int c);
int _atoi(char *s);
int interactive_mode(info_t *info);
int delimeter_char(char c, char *delimeter);
int populate_env_list(info_t *info);
int _myunsetenv(info_t *info);
int _mysetenv(info_t *info);
char *_getenv(info_t *info, const char *n);
int _myenv(info_t *info);
void ffree(char **pp);
char *_strchr(char *s, char c);
char *_strncat(char *dest, char *src, int n);
char *_strncpy(char *dest, char *src, int n);
void sigintHandler(__attribute__((unused))int sig_num);
int _getline(info_t *info, char **ptr, size_t *length);
ssize_t read_buf(info_t *info, char *buffer, size_t *i);
ssize_t get_input(info_t *info);
ssize_t input_buf(info_t *info, char **buffer, size_t *len);

#endif
