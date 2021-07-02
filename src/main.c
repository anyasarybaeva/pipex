#include "../pipex.h"

int	**make_pipe(int	size)
{
	int	**pipe;
	int	i;

	i = 0;
	if (size < 0)
		return (0);
	pipe = malloc(sizeof(int *) * (size + 2));
	if (!pipe)
		return (0);
	pipe[i++] = 0;
	while (i <= size)
	{
		pipe[i] = malloc(sizeof(int) * 2);
		if (!pipe[i++])
			return (0);
	}
	pipe[size + 1] = NULL;
	return (pipe);
}

void	pipex(char	**argv, int	argc, \
	   	char	**env)
{
	int			*fd;
	t_command	**all;
	int			i;
	int			i1;

	i1 = -1;
	fd = check_fd(argv, argc);
	if (!fd)
		return ;
	all = make_command(fd, argv, argc, env);
	redirect(fd, all, argc);
	close(fd[1]);
	free(fd);
	while (all[++i1])
	{
		i = -1;
		while (all[i1]->all[++i])
			free(all[i1]->all[i]);
		free(all[i1]->all[i]);
		free(all[i1]->all);
		free(all[i1]);
	}
	free(all);
}

int	main(int	argc, char	**argv, char	**env)
{
	extern int	errno;

	if (argc == 5)
		pipex(argv, argc, env);
	else
		ft_putendl_fd("not enoght arg", 0);
}
