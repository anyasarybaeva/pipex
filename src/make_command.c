#include "../pipex.h"

char	*ft_getenv(char	*key, char	**env)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(key);
	while (env[++i])
	{
		if (!ft_strncmp(key, env[i], len) && env[i][len] == '=')
			return (&env[i][len + 1]);
	}
	return (0);
}

char	*find_path(char	*name, char	**env)
{
	char	**PATH;
	int		i;
	char	*tmp;
	char	*tmp1;

	i = -1;
	tmp = ft_getenv("PATH", env);
	PATH = ft_split(tmp, ':');
	while (PATH[++i])
	{
		tmp1 = ft_strjoin("/", name);
		tmp = ft_strjoin(PATH[i], tmp1);
		free(tmp1);
		if (!access(tmp, 1))
		{
			free_array_of_strings(PATH);
			free(name);
			return (tmp);
		}
		free(tmp);
	}
	free_array_of_strings(PATH);
	return (name);
}

t_command	*ft_cat(char *argv, char **env)
{
	t_command	*all;

	all = malloc(sizeof(t_command) * (1));
	all->env = env;
	all->all = (char **)malloc(sizeof(char *) * 3);
	all->all[0] = ft_strdup("/bin/cat");
	all->all[1] = ft_strdup(argv);
	all->all[2] = 0;
	return (all);
}

t_command	**make_command(char	**argv, int	argc, char	**env)
{
	int			i;
	t_command	**all;
	int			i1;

	i1 = 0;
	i = 1;
	all = (t_command **)malloc(sizeof(t_command *) * (argc - 2));
	if (!all)
		return (0);
	while (++i < argc - 1)
	{
		all[i1] = malloc(sizeof(t_command) * (1));
		all[i1]->env = env;
		all[i1]->all = ft_split(argv[i], ' ');
		all[i1]->all[0] = find_path(all[i1]->all[0], env);
		i1++;
	}
	all[i1] = 0;
	return (all);
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
