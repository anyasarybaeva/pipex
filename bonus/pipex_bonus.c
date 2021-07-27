#include "../pipex.h"

int	*check_fd(char **argv, int argc)
{
	int	*fd;

	fd = malloc(sizeof(int) * 2);
	if (access(argv[1], 4) == -1 && ft_strncmp("/dev/random", argv[1], 13))
	{
		ft_putstr_fd("bash: ", 0);
		ft_putstr_fd(argv[1], 0);
		ft_putstr_fd(": ", 0);
		ft_putendl_fd(strerror(errno), 0);
		fd[0] = -100;
	}
	else
		fd[0] = open(argv[1], O_RDWR);
	fd[1] = open (argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777 );
	if (fd[1] == -1)
	{
		ft_putstr_fd("bash: ", 0);
		ft_putstr_fd(argv[argc - 1], 0);
		ft_putstr_fd(": ", 0);
		ft_putendl_fd(strerror(errno), 0);
		return (0);
	}
	return (fd);
}

void	free_pipe(int **pipe, pid_t	*pid)
{
	int	i;

	i = 0;
	free(pipe[i++]);
	while (pipe[i])
		free(pipe[i++]);
	free(pipe[i]);
	free(pipe);
	free(pid);
}
