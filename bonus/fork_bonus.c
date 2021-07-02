#include "../pipex.h"

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

void	redirect(int *fd, t_command **all, int size)
{
	int		**pipe;
	int		i;
	pid_t	*pid;
	int		num;

	i = 0;
	num = size - 5 + fd[0];
	pipe = make_pipe(size - 5 + fd[0]);
	pid = malloc(sizeof(pid) * (size - 4 + fd[0]));
	if (!pid)
		return ;
	pid[i] = test(all[num--], pipe[i], pipe[i + 1], fd[1]);
	while (0 <= num)
	{
		i++;
		pid[i] = test(all[num--], pipe[i], pipe[i + 1], 0);
	}
	print_errors(pid, all, i);
	free_pipe(pipe, pid);
}

void	print_errors(pid_t	*pid, t_command **all, int size)
{
	int	fd1;
	int	i;

	i = 0;
	while (size >= 0)
	{	
		waitpid(pid[size], &fd1, 0);
		if (access(all[i]->all[0], 1))
		{
			ft_putstr_fd("bash: command not found:", 0);
			ft_putstr_fd(all[i]->all[0], 0);
			ft_putstr_fd("\n", 0);
		}	
		size--;
		i++;
	}
}

void	redirect_pipe(int	*pipe, int	where)
{
	if (pipe != 0)
	{
		dup2(pipe[where], where);
		close(pipe[1]);
		close(pipe[0]);
	}
}

pid_t	test(t_command	*all, int	*pipe_1, int	*pipe_2, int	fd1)
{
	pid_t	pid;

	if (pipe_2 != 0)
		pipe(pipe_2);
	pid = fork();
	if (!pid)
	{
		redirect_pipe(pipe_1, 1);
		redirect_pipe(pipe_2, 0);
		if (fd1)
		{
			dup2(fd1, 1);
			close(fd1);
		}	
		if (access(all->all[0], 1) || execve(all->all[0], all->all, all->env))
			exit(0);
	}
	if (pipe_1 != 0)
	{
		close(pipe_1[1]);
		close(pipe_1[0]);
	}
	return (pid);
}
