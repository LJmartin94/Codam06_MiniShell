/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage_execution.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 16:06:45 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/04 14:36:35 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include "error.h"


#include <sys/types.h>//
#include <sys/stat.h>//


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
		e_close(fd);
		return ;
	}
	else if (ft_strncmp(comp->sep, "|", 2) == 0)
	{
		dup2(p_fd[1], STDOUT_FILENO);
		e_close(p_fd[0]);
		e_close(p_fd[1]);
		return;
	}
	else
		return ;
	dup2(fd, STDOUT_FILENO);
	e_close(fd);
}

void free_matrix(char **matrix)
{
	size_t i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
}

char *find_dir(t_vector *env, t_icomp *comp)
{
	t_env *path;
	char **paths;
	size_t i;
	struct stat stat_struct;

	path = vector_get(env, vector_search(env, compare_key, "PATH"));
	paths = ft_split(path->value, ':');
	i = 0;
	while(paths[i] != NULL)
	{
		char *tmp = ft_strjoin(paths[i], "/");
		char *final = ft_strjoin(tmp, comp->cmd);
		free(tmp);
		if (stat(final, &stat_struct) == 0)
		{
			free_matrix(paths);
			paths = NULL;
			return (final);
		}
		free(final);
		i++;
	}
	free_matrix(paths);
	paths = NULL;
	return (NULL);
}

void run_command(t_cmd f, t_vector *env, t_icomp *comp, int fd[2])
{
	char *path;
	char **envp;
	char **argv;

	handle_redirections(comp, fd);
	if (f != NULL)
		f(env, comp);
	else
	{
		path = find_dir(env, comp);
		if (path == NULL)
		{
			invalid_cmd(comp);
			exit(0);
		}
		envp = env_to_envp(env);
		free_environment(env);
		argv = build_argv(comp);
		execve(path, argv,  envp);
	}
	exit(0);
}

int	cmp_pid(int *pid1, int *pid2)
{
	return (*pid1 - *pid2);
}

int pid_print_aa(int fd, int *pid)
{
	return (ft_dprintf(fd, "pid: %d\n", *pid));
}

void parent_process(t_icomp *comp, int pid, int fd[2], int stdin)
{
	int *pid_malloc;
	int *pid_item;

	pid_malloc = (int *)e_malloc(sizeof(int)); //TODO: try to close here, wait for some time, if not closed yet, save value and continue
	*pid_malloc = pid;
	vector_push(&g_pid_list, pid_malloc);
	if (stdin != -1)// if there is piped input. //TODO: Test if this works with pipe but fd = -1
	{
		int item_index = vector_search(&g_pid_list, cmp_pid, pid_malloc);
		e_close(stdin); //TODO: I should close this (stdin from previous process) when the the current process has terminated
		if (item_index > 0)
		{
			pid_item = vector_get(&g_pid_list, item_index - 1);
			wait(pid_item);
			free(pid_item);
			vector_delete(&g_pid_list, item_index - 1);
		}
		else
		{
			ft_dprintf(STDOUT_FILENO, "Something's wrong with pids and pipes\n");
		}
	}
	if (ft_strncmp(comp->sep, "|", 2) != 0)
	{
		wait(&pid);
		int index = vector_search(&g_pid_list, cmp_pid, pid_malloc);
		vector_delete(&g_pid_list, index);
		free(pid_malloc);
	}
	e_close(fd[1]);
}

int exec_command(t_vector *env, t_icomp *comp, int stdin)
{
	int		pid; //TODO: ??
	t_cmd	f;
	int		fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (ft_strncmp(comp->sep, "|", 2) == 0)
	{
		if (pipe(fd) == -1) //TODO: change this
			error_exit_errno();
	}
	f = get_command(comp);
	pid = fork();
	if (pid == 0)
	{
		if (stdin != -1)
		{
			dup2(stdin, STDIN_FILENO);
			e_close(stdin); //TODO: Should i check return value for e_close?
		}
		run_command(f, env, comp, fd); //TODO: if prev is invalid command, don't do second part
	}
	else 
		parent_process(comp, pid, fd, stdin);
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

//TODO: Shell doesn't handle closing infinite processes

//TODO: fd leaks????spooky


// $> base64 /dev/urandom | head -c 1000 | rev | cat -e | cut -d 'x' -f 1,3,5 >> /tmp/toto.txt; cat /tmp/toto.txt; rm /tmp/toto.txt
// $> base64 < /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e s/1/Yes/g -e s/0/No/g; ps a | grep 'base64' | grep -v 'grep' <- this doesn't work due to parsing

//In what order should things execute? Redirections occur before command finishes, other commands wait for previosu commands to finish, pipes don't wait for previous commands to finish
