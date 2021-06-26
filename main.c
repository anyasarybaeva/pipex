#include "pipex.h"
void	free_array_of_strings(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		array[i++] = 0;
	while (i >= 0)
		free(array[i--]);
	free(array);
}
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
int *check_fd(char **argv, int argc)
{
	int *fd;

	fd=malloc(sizeof(int)*2);
    fd[0]=open(argv[1],O_WRONLY);
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
    return(fd);
}
t_command   **make_command(char **argv, int argc)
{
    int i;
    t_command **all;
    int i1;

    i1 = 0;
    i = 1;
    all=(t_command**)malloc(sizeof(t_command *)*(argc-3));
    if(!all)
        return(0);
    while(++i<argc-1)
    {
		all[i1]=malloc(sizeof(t_command)*(1));
        all[i1]->all=ft_split(argv[i],' ');
        all[i1]->all[0]=find_path(all[i1]->all[0]);
		printf("com:%s\n",all[i1]->all[0]);
        i1++;
    }
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
		tmp=ft_strjoin("/",name);
		tmp = ft_strjoin(PATH[i],tmp);
		if(!stat(tmp,&buff))
		{
			//free_array_of_strings(PATH);
			return(tmp);
		}
		free(tmp);
	}
	//free_array_of_strings(PATH);
	return(name);
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

void print_errors(pid_t *pid,t_command  **all,int size)
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
			ft_putstr_fd(all[i]->all[0],0);
			ft_putstr_fd("\n",0);
		}
		size--;
        i++;
	}

}

pid_t test(t_command *all,int *pipe_1,int *pipe_2,int fd1,int fd2, char **env)
{
	struct stat buff;
	if(pipe_2!=0)
		pipe(pipe_2);
	pid_t pid=fork();
	if(!pid)
	{
		if(pipe_1!=0)
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
		if(stat(all->all[0],&buff))
			exit(1);		
		if(execve(all->all[0],all->all,env))
			exit(0);
	}
	if(pipe_1!=0)
	{
		close(pipe_1[1]);
		close(pipe_1[0]);
	}
	return(pid);
}
void redirect(int *fd, t_command **all, char **env, int size)
{
    int **pipe;
	int i;
	pid_t *pid;
	int num;
	num=size-4;
	
    i = 0;
    pipe = make_pipe(size-4);
	pid=malloc(sizeof(pid)*(size-3));
	if(!pid)
		return;
    pid[i]=test(all[num--],pipe[i],pipe[i+1],fd[1],0,env);
	i++;
	while(0<num)
	{
        pid[i]=test(all[num--],pipe[i],pipe[i+1],0,0,env);
		i++;
	}
	pid[i]=test(all[num],pipe[i],pipe[i+1],0,fd[0],env);
	printf("hello\n");
	waitpid(pid[0],&num,0);
	printf("hello1\n");
	waitpid(pid[1],&num,0);
	//print_errors(pid,all,size);
	//i=size;
	//i = 0;
	//free(pipe[i++]);
	//while(pipe[i])
	//	free(pipe[i++]);
	//free(pipe[i]);
	///free(pipe);
	//free(pid);
}

void pipex(char **argv, int argc, char **env)
{
    int *fd;
	t_command **all;
    int i;

    i=-1;
    fd=check_fd(argv, argc);
	if(!fd)
		return ;
	all = make_command(argv, argc);
	redirect(fd,all,env, argc);
    //close(fd[0]);
    //close(fd[1]);
   // free(fd);
   // while (all->all[++i])
     //   free(all[i]);
    //free(all[i]);
    //free(all);
}

int main(int argc,char **argv, char **env)
{
    int fd;
    if(argc==5)
        pipex(argv, argc,env);
    else
        printf("not enoght arg\n");
}