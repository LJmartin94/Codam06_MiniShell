/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage_execution.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 16:06:45 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/17 20:50:29 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

void			run_command(t_cmd f, t_vector *env, t_icomp *comp)
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

static void		kill_processes(t_vector *fd_list, t_vector *pid_list)
{
	int *fd_ptr;
	int *pid_ptr;
	int wstatus;

	while (fd_list->amt > 0)
	{
		fd_ptr = vector_get(fd_list, 0);
		e_close(*fd_ptr);
		free(fd_ptr);
		vector_delete(fd_list, 0);
	}
	while (pid_list->amt > 0)
	{
		pid_ptr = vector_get(pid_list, 0);
		waitpid(*pid_ptr, &wstatus, 0);
		g_ret_val = WEXITSTATUS(wstatus);
		free(pid_ptr);
		vector_delete(pid_list, 0);
		g_amt_processes = pid_list->amt;
	}
}

static void		parent_process(t_icomp *comp, int pid, int fd[2], t_vector *fd_list, t_vector *pid_list)
{
	int *fd_ptr;
	int *pid_ptr;

	if (fd[1] != -1)
		e_close(fd[1]);
	fd_ptr = (int *)e_malloc(sizeof(int));
	pid_ptr = (int *)e_malloc(sizeof(int));
	*fd_ptr = fd[0];
	*pid_ptr = pid;
	vector_push(fd_list, fd_ptr);
	vector_push(pid_list, pid_ptr);
	g_amt_processes = pid_list->amt;
	if (comp->right == NULL)
		kill_processes(fd_list, pid_list);
}

static int		shnell_execute(t_cmd f, t_vector *env, t_icomp *comp, int input)
{
	int fd;

	if (f != NULL && ft_strncmp(comp->sep, "|", 2) != 0 && input == -1)
	{
		fd = redirect_builtin(comp);
		g_ret_val = f(env, comp, fd);
		return (1);
	}
	return (0);
}

int				exec_command(t_vector *env, t_icomp *comp, int input, t_vector *fd_list, t_vector *pid_list)
{
	t_cmd	f;
	int		pid;
	int		fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (ft_strncmp(comp->sep, "|", 2) == 0)
	{
		if (pipe(fd) == -1)
			error_exit_errno();
	}
	f = get_command(comp);
	if (shnell_execute(f, env, comp, input) == 0)
	{
		pid = fork();
		if (pid == -1)
			error_exit_errno();
		else if (pid == 0)
		{
			handle_redirections(comp, fd, input);
			run_command(f, env, comp);
		}
		else
			parent_process(comp, pid, fd, fd_list, pid_list);
	}
	return (fd[0]);
}
