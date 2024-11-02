#ifndef SIGNALS_MAIN
#define SIGNALS_MAIN

#include <stdio.h>
#include <signal.h>
#include <errno.h>

int handle_signal(void);
void do_instead(int);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);
int pid_exist(pid_t pid);


#endif