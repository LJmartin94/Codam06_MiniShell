/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage_execution.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 16:06:45 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/03 11:52:16 by jsaariko      ########   odam.nl         */
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
	//TODO: free matrix (do i need to?? It'll exit regardless)
	return (argv);
}

char	*readdir_test(t_vector *env, t_icomp *comp) // TODO: Try to do this with stat
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

void	handle_redirections(t_icomp *comp, int p_fd[2])
{
	int fd;

	if (ft_strncmp(comp->sep, ">>", 3) == 0)	
		fd = open(comp->right->cmd, O_WRONLY|O_CREAT|O_APPEND, 0666);
	else if (ft_strncmp(comp->sep, ">", 2) == 0)
		fd = open(comp->right->cmd, O_WRONLY|O_CREAT|O_TRUNC, 0666);
	else if (ft_strncmp(comp->sep, "<", 3) == 0)	
	{
		fd = open(comp->right->cmd, O_RDONLY, 0666);
		if (fd == -1)
		{
			ft_dprintf(STDERR_FILENO, "oops, no such file\n"); //TODO: change error handling
			exit(0);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		return ;
	}
	else if (ft_strncmp(comp->sep, "|", 2) == 0)
	{
		dup2(p_fd[1], STDOUT_FILENO);
		close(p_fd[0]);
		close(p_fd[1]);
		return;
	}
	else
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void run_command(t_cmd f, t_vector *env, t_icomp *comp, int fd[2])
{
	handle_redirections(comp, fd);
	if (f != NULL)
		f(env, comp);
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
	}
	exit(0);
}

int exec_command(t_vector *env, t_icomp *comp, int stdin)
{
	int		pid; //TODO: ??
	t_cmd	f;
	int		fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (pipe(fd) == -1) //TODO: change this
		error_exit_errno();
	(void)stdin;
	f = get_command(comp);
	pid = fork();
	if (pid == 0)
	{
		if (stdin != -1)
		{
			dup2(stdin, STDIN_FILENO);
			close(stdin);
		}
		run_command(f, env, comp, fd);
	}
	else 
	{
		wait(&pid);
		close(fd[1]);
	}
	return (fd[0]);
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


/*
** > env -i bash
bash-3.2$ env
PWD=/Users/jules/projects/codam/minishell
SHLVL=1
_=/usr/bin/env

//TODO: ls doesn't have to work if path is not set from the start. Also if path is unset during testing, it doesn't have to find path
//TODO: what is the _ env variable
*/