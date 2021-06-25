#include "pipex.h"
void	ft_putstr_fd(char *s, int fd)
{
	size_t i;

	i = 0;
	if (s)
		while (s[i] != '\0')
		{
			write(fd, &s[i], 1);
			i++;
		}
}
int check_fd(char **argv, int argc, int **fd)
{
    fd[0]=open(argv[1],O_RDONLY);
    if(fd[0]==-1)
    {    
        printf("error: outfile\n");
        return(0);
    }
    fd[1]=open(argv[argc-1], O_WRONLY | O_CREAT);
    if(fd[1]==-1)
    {
        printf("error: infile\n");
        return(0);
    }
    return(1);
}
char   **make_command(char **argv, int argc)
{
    int i;
    char **all;
    int i1;

    i = 0;
    i = 1;
    all=(char**)malloc(sizeof(char *)*(argc-1));
    if(!all)
        return(0);
    while(argv[++i])
    {
        all[i1]=ft_split(argv[i],' ');
        all[i1][0]=find_path(all[i1][0]);
        i1++;
    }
    all[i1]=0;
    return(all);
}
char  *find_path(char *name)
{
	char **PATH;
	int i;
	char *tmp;
	struct stat buff;
	i = -1;
	tmp = getenv("PATH");
	PATH = ft_split(tmp,':');
	while(PATH[++i])
	{
		
		tmp = ft_strjoin(PATH[i],name);
		if(!stat(tmp,&buff))
		{
			free_array_of_strings(PATH);
			return(tmp);
		}
		printf("%s\n",tmp);
		free(tmp);
	}
	free_array_of_strings(PATH);
	return(0);
}
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
	pipe[i++] = NULL;
	while (i <= size)
	{
		pipe[i] = malloc(sizeof(int) * 2);
		if (!pipe[i++])
			return (0);
	}
	pipe[size + 1] = NULL;
	return (pipe);
}

void print_errors(pid_t *pid,char  **all,int size)
{
	int fd1;
    int i;

    i = 0;
	while(size>=0)
	{	
		waitpid(pid[size],&fd1,0);
		if(fd1==256)
		{
			ft_putstr_fd("zsh: command not found:",0);
			ft_putstr_fd(all[i],0);
			ft_putstr_fd("\n",0);
		}
		size--;
        i++;
	}

}

pid_t test(char **all,int *pipe_1,int *pipe_2,int fd1,int fd2, char **env)
{
	struct stat buff;
	if(pipe_2!=0)
		pipe(pipe_2);
	pid_t pid=fork();
	if(!pid)
	{
		if(pipe_1!=0 )
		{
			dup2(pipe_1[1],1);
			close(pipe_1[1]);
			close(pipe_1[0]);//add function close_fd -5 lines
		}
		if(pipe_2!=0)
		{
			dup2(pipe_2[0],0);
			close(pipe_2[1]);
			close(pipe_2[0]);
		}
		if(fd1)
		{
			dup2(fd1,1);
			close(fd1);
		}
		if(fd2)
		{
			dup2(fd2,0);
			close(fd2);
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
void redirect(int *fd, char **all, char **env, int size)
{
    int **pape;
	int i;
	pid_t *pid;
	
    i = 0;
    pipe = make_pipe(size);
	pid=malloc(sizeof(pid)*(size+1));
	if(!pid)
		return;
    pid[size--]=test(all[i],pipe[i],pipe[i+1],fd[0],0,env);
	while(0<=size)
	{
        i++;
        if(0==size)
            pid[size]=test(all[i],pipe[i],pipe[i+1],0,fd[1],env);
        else
           pid[size]=test(all[i],pipe[i],pipe[i+1],0,0,env); 
           size--;
	}
	print_errors(pid,all,size);
	i=size;
	i = 0;
	free(pipe[i++]);
	while(pipe[i])
		free(pipe[i++]);
	free(pipe[i]);
	free(pipe);
	free(pid);
}

void pipex(char **argv, int argc, char **env)
{
    int fd[2];
    char **all;
    int i;

    i=-1;
    if(check_fd(argv, argc, &fd))
        return ;
    all = make_command(argv, argc);
    redirect(fd,all,env, argc-2);
    close(fd[0]);
    close(fd[1]);
    free(fd);
    while (all[++i])
        free(all[i]);
    free(all[i]);
    free(all);
}

int main(int argc,char **argv, char **env)
{
    int fd;
    if(argc==5)
        pipex(argv, argc,env);
    else
        printf("not enoght arg\n");
}