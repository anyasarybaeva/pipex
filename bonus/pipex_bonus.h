#ifndef PIPEX_H
# define PIPEX_H

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include<stdio.h>
int check_fd(char **argv, int argc, int **fd);
char   **make_command(char **argv, int argc);
char  *find_path(char *name);
void pipex(char **argv, int argc);
void redirect(int *fd, char **all, char **env, int size);
pid_t test(char **all,int *pipe_1,int *pipe_2,int fd1,int fd2, char **env);
void print_errors(pid_t *pid,char  **all,int size);
int	**make_pipe(int	size);
#endif
