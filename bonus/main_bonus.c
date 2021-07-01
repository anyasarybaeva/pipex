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
	pipe[i++]=0;
	while (i <= size)
	{
		pipe[i] = malloc(sizeof(int) * 2);
		if (!pipe[i++])
			return (0);
	}
	pipe[size + 1] = NULL;
	return (pipe);
}
pid_t test(char **all,int *pipe_1,int *pipe_2,int fd1, char **env)
{
	struct stat buff;
	if(pipe_2!=0)
		pipe(pipe_2);
	pid_t pid=fork();
	if(!pid)
	{
		if(pipe_1 != 0)
		{
			dup2(pipe_1[1],1);
			close(pipe_1[1]);
			close(pipe_1[0]);//add function close_fd -5 lines
		}
		if(pipe_2 != 0)
		{
			dup2(pipe_2[0], 0);
			close(pipe_2[1]);
			close(pipe_2[0]);
		}
		if(fd1)
		{
			dup2(fd1, 1);
			close(fd1);
		}
		if(stat(all[0],&buff))
			exit(1);		
		if(execve(all[0],all,env))
			exit(0);
	}
	if(pipe_1!=0)
	{
		close(pipe_1[1]);
		close(pipe_1[0]);
	}
	return(pid);
}


void pipex(char **argv, int argc, char **env)
{
    int *fd;
	t_command **all;
    int i;
	int i1=-1;

    fd=check_fd(argv, argc);
	if(!fd)
		return ;
	all = make_command(fd, argv, argc);
	redirect(fd,all,env, argc);
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

int main(int argc,char **argv, char **env)
{
    if(argc>=5)
        pipex(argv, argc,env);
    else
        printf("not enoght arg\n");	
}