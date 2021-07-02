#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h> 
# include <stdlib.h>
# include <sys/ioctl.h>
# include <errno.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

typedef struct s_command
{
	char	**all;
	char	**env;
}		t_command;
int			*check_fd(char	**argv, int	argc);
t_command	**make_command(int	*fd, char	**argv, int	argc, char	**env);
char		*find_path(char	*name, char	**env);
void		pipex(char **argv, int argc, char **env);
void		redirect(int	*fd, t_command	**all, int	size);
pid_t		test(t_command	*all, int	*pipe_1, int	*pipe_2, int	fd1);
void		print_errors(pid_t	*pid, t_command	**all, int	size);
int			**make_pipe(int	size);
char		**ft_split(char const	*s, char	c);
void		free_array_of_strings(char	**array);

#endif
