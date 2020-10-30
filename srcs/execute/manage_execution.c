/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage_execution.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 16:06:45 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/30 17:12:37 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include "error.h"

char	**build_argv(t_icomp *comp)
{
	int i = 0;
	int j = 0;
	char **try = ft_split(comp->arg, ' ');
	while(try[i] != NULL)
	{
		i++;
	}
	char **argv = (char **)e_malloc(i + 1);
	argv[j] = comp->cmd;//change
	j++;
	i = 0;
	while(try[i] != NULL)
	{
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
	char **split = ft_split(item->value, ':');
	int i;
	i = 0;
	char *found;
	found = NULL;
	while(split[i] != NULL)
	{
		i++;
	}
	DIR *dir;
	int j = 0;
	while(split[j] != NULL)
	{
		dir = opendir(split[j]);
		if (dir == NULL)
			break ;
		struct dirent *entry;
		entry = readdir(dir);
		while ((entry = readdir(dir)) != NULL)
		{
			if (ft_strncmp(entry->d_name, comp->cmd, ft_strlen(comp->cmd) + 1) == 0)
			{
				found = ft_strjoin(split[j], "/");
				closedir(dir); //TODO: free all the shit
				return (found);
			}
		}
		closedir(dir);
		j++;
	}
	return (NULL);
	(void)comp;
}


void	handle_redirections(t_icomp *comp)
{
	int fd;

	if (ft_strncmp(comp->sep, ">>", 3) == 0)	
		fd = open(comp->right->cmd, O_WRONLY|O_CREAT|O_APPEND, 0666);
	else if (ft_strncmp(comp->sep, ">", 2) == 0)
		fd = open(comp->right->cmd, O_WRONLY|O_CREAT|O_TRUNC, 0666);
	else
		return ;		
	dup2(fd, 1);
	close(fd);
}

// TODO: Redirections >, >> and <
// TODO: If &&, stop executing everything linked by && once prev one failed
// TODO: If ;, failure doesn't affect others
// TODO: If |, at failure of first command, second half doesn't execute. Also do the whole pipe thing
void run_command(t_cmd f, t_vector *env, t_icomp *comp)
{
	handle_redirections(comp); //TODO: This dup does not seem to work with a normal function. Do i have to pipe it anyway?
	if (f != NULL)
	{
		f(env, comp);
		exit(0);
	}
	else
	{
		char *dir= readdir_test(env, comp);
		if (dir == NULL)
		{
			invalid_cmd(comp);
			exit(0);
		}
		char **envp;
		char **argv;
		char *command = ft_strjoin(dir, comp->cmd);
		envp = env_to_envp(env);
		free_environment(env);
		argv = build_argv(comp);
		execve(command, argv,  envp);
		exit(0);
	}
}


void	exec_command(t_vector *env, t_icomp *comp)
{
	int		pid;
	t_cmd	f;
	// int		g_pid[4];

	f = get_command(comp);
	pid = fork();
	if (pid != 0) //if in parent process
	{
		wait(&pid);

	}
	else
	{
		run_command(f, env, comp);
	}
}


//Built-in commands are contained within the shell itself. When the name of a built-in command is used as the first word of a simple command, the shell executes the command directly, without creating a new process. Built-in commands are necessary to implement functionality impossible or inconvenient to obtain with separate utilities.



//TODO: Tests:
/*
while true; do rm file ; echo "123" > file | echo "abcdefg" > file ; cat file ; echo ------; sleep 1; done

rm file ; echo "123" > file | echo "abcdefg" > file
> cat file
123
efg
rm file ; echo "123" > file | echo "abcdefg" > file
> cat file
123
rm file ; echo "123" > file | echo "abcdefg" > file
> cat file
abcdefg
*/