#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <ctype.h>

int ** pipes;
pid_t * child_pids;
int MaxChildNum;
int child_count;

void free_all (int ** pipes,  pid_t * child_pids);
void child_handler(int signum);
void child_process(int file_index, char *filename);