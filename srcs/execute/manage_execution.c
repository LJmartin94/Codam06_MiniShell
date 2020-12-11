/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage_execution.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 16:06:45 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/06 15:47:50 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include <sys/wait.h>

static void	run_command(t_cmd f, t_vector *env, t_icomp *comp)
{
	char *path;
	char **envp;
	char **argv;

	if (f != NULL)
		f(env, comp, STDOUT_FILENO);
	else if (comp->cmd[0] != '\0')
	{
		path = find_path(env, comp);
		if (path == NULL)
			invalid_cmd(comp);
		envp = env_to_envp(env);
		free_env(env);
		argv = build_argv(comp);
		if (execve(path, argv, envp) == -1)
			error_exit_errno();
	}
	exit(0);
}

static void	parent_process(int pid, int fd[2],
				t_vector *fd_list, t_vector *pid_list)
{
	int *fd_ptr;
	int *pid_ptr;

	fd_ptr = (int *)e_malloc(sizeof(int));
	pid_ptr = (int *)e_malloc(sizeof(int));
	if (fd[1] != -1)
		e_close(fd[1]);
	*fd_ptr = fd[0];
	*pid_ptr = pid;
	vector_push(fd_list, fd_ptr);
	vector_push(pid_list, pid_ptr);
	g_amt_processes = pid_list->amt;
}

static int	main_process(t_icomp *comp, t_vector *env, t_cmd *f, int fd[2])
{
	t_cmd	f_tmp;

	if (ft_strncmp(comp->sep, "|", 2) == 0)
	{
		if (pipe(fd) == -1)
			error_exit_errno();
	}
	f_tmp = get_command(comp);
	if (f_tmp != NULL && ft_strncmp(comp->sep, "|", 2) != 0 &&
		(comp->left == NULL ||
		(comp->left && ft_strncmp(comp->left->sep, "|", 2) != 0)))
	{
		g_ret_val = f_tmp(env, comp, redirect_builtin(comp));
		return (1);
	}
	else
	{
		*f = f_tmp;
		return (0);
	}
}

void		exec_command(t_vector *env, t_icomp *comp,
				t_vector *fd_list, t_vector *pid_list)
{
	t_cmd	f;
	int		pid;
	int		fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (main_process(comp, env, &f, fd) == 0)
	{
		pid = fork();
		if (pid == -1)
			error_exit_errno();
		else if (pid == 0)
		{
			handle_redirections(comp, fd, fd_list);
			run_command(f, env, comp);
		}
		else
			parent_process(pid, fd, fd_list, pid_list);
	}
}
