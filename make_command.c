#include "pipex.h"
char  *find_path(char *name)
{
	char **PATH;
	int i;
	char *tmp;
	char *tmp1;
	struct stat buff;
	i = -1;
	tmp = getenv("PATH");
	PATH = ft_split(tmp,':');
	while(PATH[++i])
	{
		tmp1=ft_strjoin("/",name);
		tmp = ft_strjoin(PATH[i],tmp1);
		free(tmp1);
		if(!stat(tmp,&buff))
		{
			free_array_of_strings(PATH);
			free(name);
			return(tmp);
		}
		free(tmp);
	}
	free_array_of_strings(PATH);
	return(name);
}

t_command   **make_command(int *fd,char **argv, int argc)
{
    int i;
    t_command **all;
    int i1;

    i1 = 0;
    i = 1;
    all=(t_command**)malloc(sizeof(t_command *)*(argc-3+fd[0]));
    if(!all)
        return(0);
	if(fd[0])
	{
		all[i1]=malloc(sizeof(t_command)*(1));
		all[i1]->all=(char **)malloc(sizeof(char*)*3);
		all[i1]->all[0]=ft_strdup("/bin/cat");
		all[i1]->all[1]=ft_strdup(argv[1]);
		all[i1++]->all[2]=0;
	}
    else
        i = 2;
    while(++i<argc-1)
    {
		all[i1]=malloc(sizeof(t_command)*(1));
        all[i1]->all=ft_split(argv[i],' ');
        all[i1]->all[0]=find_path(all[i1]->all[0]);
		printf("com:%s\n",all[i1]->all[0]);
        i1++;
    }
	all[i1]=0;
    return(all);
}

void	free_array_of_strings(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array[i]);
	free(array);
}