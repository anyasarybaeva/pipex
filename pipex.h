#ifndef PIPEX_H
# define PIPEX_H

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include<stdio.h>
# include <stdio.h>
# include <curses.h>
# include <termios.h> 
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <term.h>
# include <string.h>
# include <errno.h>
#include "libft/libft.h"
typedef struct s_command
{
	char **all;
}			t_command;
int *check_fd(char **argv, int argc);
t_command   **make_command(char **argv, int argc);
char  *find_path(char *name);
void pipex(char **argv, int argc,char **env);
void redirect(int *fd, t_command **all, char **env, int size);
pid_t test(t_command *all,int *pipe_1,int *pipe_2,int fd1,int fd2, char **env);
void print_errors(pid_t *pid,t_command  **all,int size);
int	**make_pipe(int	size);
char	**ft_split(char const *s, char c);
#endif
