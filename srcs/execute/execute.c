/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/05 12:18:56 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "error.h"

/*
** TODO: Build command validators in functions
*/

t_cmd		get_command(t_icomp *comp)
{
	if (ft_strncmp(comp->cmd, "echo", 5) == 0)
		return (ft_echo);
	if (ft_strncmp(comp->cmd, "exit", 5) == 0)
		return (ft_exit);
	if (ft_strncmp(comp->cmd, "env", 4) == 0)
		return (ft_env);
	if (ft_strncmp(comp->cmd, "unset", 6) == 0)
		return (ft_unset);
	if (ft_strncmp(comp->cmd, "export", 7) == 0)
		return (ft_export);
	if (ft_strncmp(comp->cmd, "pwd", 4) == 0)
		return (ft_pwd);
	if (ft_strncmp(comp->cmd, "cd", 3) == 0)
		return (ft_cd);
	return (NULL);
}

static void	kill_processes(t_vector *fd_list, t_vector *pid_list)
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

void		execute(t_vector *env, t_icomp *comp)
{
	t_icomp		*tmp;
	t_vector	fd_list;
	t_vector	pid_list;

	vector_init(&fd_list);
	vector_init(&pid_list);
	tmp = comp;
	while (tmp != NULL)
	{
		exec_command(env, tmp, &fd_list, &pid_list);
		tmp = tmp->right;
	}
	kill_processes(&fd_list, &pid_list);
}
