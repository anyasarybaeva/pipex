#include "../pipex.h"

int	*check_fd(char **argv, int argc)
{
	int	*fd;

	fd = malloc(sizeof(int) * 2);
	if (access(argv[1], 3) == -1 && ft_strncmp("/dev/random",argv[1],13))
	{
		ft_putstr_fd("bash: ", 0);
		ft_putstr_fd(argv[1], 0);
		ft_putstr_fd(": ", 0);
		ft_putendl_fd(strerror(errno), 0);
		fd[0] = 0;
	}
	else
		fd[0] = 1;
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
