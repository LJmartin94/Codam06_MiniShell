/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage_execution.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 16:06:45 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/16 17:58:55 by jsaariko      ########   odam.nl         */
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

/*
** //TODO: what to do if index not found?
*/

static void		finish_process(int index)
{
	t_process	*pid_item;
	int			wstatus;

	pid_item = vector_get(&g_pid_list, index);
	if (pid_item == NULL)
		return ;
	// e_close(pid_item->fd);
	waitpid(pid_item->pid, &wstatus, 0);
	g_ret_val = WEXITSTATUS(wstatus);
	free(pid_item);
	vector_delete(&g_pid_list, index);
}

static void		murder_fd(size_t index)
{
	t_process *pid_item = vector_get(&g_pid_list, index);
	if (pid_item == NULL)
		return ;
	e_close(pid_item->fd);
}

static void		parent_process(t_icomp *comp, int pid, int fd[2], int input)
{
	t_process	*pid_malloc;
	int			item_index;

	ft_dprintf(STDOUT_FILENO, "pid of child: %d. cmd: %s\n", pid, comp->cmd);
	e_close(fd[1]);
	pid_malloc = (t_process *)e_malloc(sizeof(t_process));
	pid_malloc->pid = pid;
	pid_malloc->fd = fd[0];
	vector_push(&g_pid_list, pid_malloc);
	if (input != -1 && ft_strncmp(comp->sep, "|", 2) != 0)
	{
		size_t i = 0;
		while (i < g_pid_list.amt)
		{
			murder_fd(i);
			i++;
		}
		while (g_pid_list.amt > 0)
		{
			ft_dprintf(STDOUT_FILENO, "amt: %d\n", g_pid_list.amt);
			ft_dprintf(STDOUT_FILENO, "aaaaaaaa\n");
			finish_process(0);
		}
	}
	else if (input == -1 && ft_strncmp(comp->sep, "|", 2) != 0)
	{
		item_index = vector_search(&g_pid_list, cmp_pid, pid_malloc);
		if (item_index >= 0)
			finish_process(item_index);
		else
			ft_dprintf(STDOUT_FILENO, "fuck, g_pid_list is fucked\n");
	}
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

int				exec_command(t_vector *env, t_icomp *comp, int input)
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
		if (pid == 0)
		{
			handle_redirections(comp, fd, input);
			run_command(f, env, comp);
		}
		else
			parent_process(comp, pid, fd, input);
	}
	return (fd[0]);
}
