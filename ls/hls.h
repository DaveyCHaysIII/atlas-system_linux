#ifndef HLS_H
#define HLS_H

/* standard library */
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>

/* hls.c */
int list_directory(const char *, char *, int *);
char *path_maker(const char *, char *);
void print_handler(struct dirent *, struct stat *, int *);

/* hls_handlers.c */
void error_handler(char *, const char*, int);
int path_validator(const char *, char *, struct stat *);
void flag_init(int *, int, char **);

#endif
