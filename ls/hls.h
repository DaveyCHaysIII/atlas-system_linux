#ifndef HLS_H
#define HLS_H

/* standard library */
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
/* extra libraries JUST for -l*/
#include<time.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<unistd.h>

/* hls.c */
int list_directory(const char *, char *, int *);
char *path_maker(const char *, char *);
void print_handler(struct dirent *, struct stat *, int *);

/* hls_handlers.c */
void error_handler(char *, const char*, int);
int path_validator(const char *, char *, struct stat *);
void flag_init(int *, int, char **);
void multi_print(int, char **, struct stat *, int *);
void print_file_info(struct dirent *, struct stat *);

/*hls_tools */
int _strlen(const char *);
int _strcmp(const char *, const char *);
int list_count(int, char**);

#endif
