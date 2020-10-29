/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/29 17:32:33 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include <unistd.h>
#include "error.h"
#include <dirent.h>

/*
** TODO: Build command validators in functions
*/

t_cmd	get_command(t_icomp *comp)
{
	if (ft_strncmp(comp->cmd, "echo", 5) == 0)
		return (ft_echo);
	if (ft_strncmp(comp->cmd, "env", 4) == 0)
		return (ft_env);
	if (ft_strncmp(comp->cmd, "unset", 6) == 0)
		return (ft_unset);
	if (ft_strncmp(comp->cmd, "export", 7) == 0)
		return (ft_export);
	return (NULL);
}

char	**build_argv(t_icomp *comp)
{
	int i = 0;
	int j = 0;
	char **try = ft_split(comp->arg, ' ');
	while(try[i] != NULL)
	{
		ft_dprintf(STDIN_FILENO, "%s, %d\n", try[i], i);
		i++;
	}
	char **argv = (char **)e_malloc(i + 1);
	argv[j] = comp->cmd;//change
	j++;
	i = 0;
	while(try[i] != NULL)
	{
		ft_dprintf(STDIN_FILENO, "lol %d %d\n", i, j);
		argv[j] = try[i];
		i++;
		j++;
	}
	argv[j] = NULL;
	//free matrix
	return (argv);
}

char	*readdir_test(t_vector *env, t_icomp *comp)
{
	t_env *item = vector_get(env, vector_search(env, compare_key, "PATH"));
	ft_dprintf(STDIN_FILENO, "%s\n", item->value);
	char **split = ft_split(item->value, ':');
	int i;
	i = 0;
	char *found;
	found = NULL;
	while(split[i] != NULL)
	{
		ft_dprintf(STDIN_FILENO, "path part %d: %s\n", i, split[i]);
		i++;
	}
	ft_dprintf(STDIN_FILENO, "DONE\n");
	DIR *dir;
	// struct dirent *dp;
	int j = 0;
	while(split[j] != NULL)
	{
		dir = opendir(split[i]);
		// dp = readdir(dir);
		struct dirent *entry;
		while ((entry = readdir(dir)) != NULL)
		{
			if (ft_strncmp(entry->d_name, comp->cmd, ft_strlen(comp->cmd) + 1))
			{
				found = ft_strdup(entry->d_name);
				closedir(dir); //TODO: free all the shit
				return (found);
			}
		}
		int dir_ret = closedir(dir);
		
		ft_dprintf(STDIN_FILENO, "dir_ret: %d\n", dir_ret);
		j++;
	}
	return (NULL);
	(void)comp;
}

void	exec_command(t_vector *env, t_icomp *comp)
{
	int pid;
	char **envp;
	char **argv;

	char *dir= readdir_test(env, comp);
	if (dir == NULL)
		invalid_cmd(comp);
	char *command = ft_strjoin(dir, comp->cmd);
	ft_dprintf(STDIN_FILENO, "command: %s\n", command);	

	pid = fork();
	if (pid != 0) //if in parent process
	{
		wait(&pid);
	}
	else
	{
		envp = env_to_envp(env);
		free_environment(env);
		argv = build_argv(comp);
		execve(command, argv,  envp);
		exit(0);
	}
	
}

void	execute(t_vector *env, t_icomp *comp)
{
	t_cmd	f;
	t_icomp	*tmp;

	tmp = comp;
	while (tmp != NULL)
	{
		f = get_command(tmp);
		if (f == NULL)
			exec_command(env, comp);
		else
			f(env, tmp);
		tmp = tmp->right;
	}
}
