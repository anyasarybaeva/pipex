#include "../pipex.h"

int *check_fd(char **argv, int argc)
{
	int *fd;

	fd=malloc(sizeof(int)*2);
    if(access(argv[1],3)==-1)
    {    
        printf("bash: %s: %s\n",argv[1],strerror(errno));
		fd[0] = 0;
    }
	else
		fd[0]=2;
	fd[1] = open(argv[argc-1], O_WRONLY | O_CREAT|O_TRUNC);
    if(fd[1] == -1)
    {
        printf("bash: %s: %s\n", argv[argc-1],strerror(errno));
        return(0);
    }
    return (fd);
}

