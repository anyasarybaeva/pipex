#include "pipex.h"
void redirect(int *fd, t_command **all, char **env, int size)
{
    int **pipe;
	int i;
	pid_t *pid;
	int num;

 
    i = 0;
	num=size-5+fd[0];
    pipe = make_pipe(size-5+fd[0]);
	pid=malloc(sizeof(pid)*(size-4+fd[0]));
	if(!pid)
		return;
    pid[i]=test(all[num--]->all,pipe[i],pipe[i+1],fd[1],env);
	while(0<=num)
	{
		i++;
        pid[i]=test(all[num--]->all,pipe[i],pipe[i+1],0,env);

	}
	print_errors(pid,all,i);
	i = 0;
	free(pipe[i++]);
	while(pipe[i])
		free(pipe[i++]);
	free(pipe[i]);
	free(pipe);
	free(pid);
}
void	print_errors(pid_t	*pid,t_command **all, int size)
{
	int	fd1;
	int i;

	i = 0;
	while (size >= 0)
	{	
		waitpid(pid[size], &fd1, 0);
		if(fd1 == 256)
		{
			ft_putstr_fd("bash: command not found:", 0);
			ft_putstr_fd(all[i]->all[0], 0);
			ft_putstr_fd("\n", 0);
		}	
		size--;
		i++;
	}
}