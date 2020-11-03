/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/03 15:02:01 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "error.h"


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

int pid_print(int fd, int *pid)
{
	return (ft_dprintf(fd, "pid: %d\n", *pid));
}

void	execute(t_vector *env, t_icomp *comp)
{
	t_icomp	*tmp;
	int 	stdin;
	int i;


	vector_init(&g_pid_list);
	i = 0;
	tmp = comp;
	stdin = -1;
	while (tmp != NULL)
	{
		stdin = exec_command(env, tmp, stdin);
		// ft_dprintf(STDOUT_FILENO, "PRINTING PIDS:\n");
		// vector_debug(STDOUT_FILENO, g_pid_list, pid_print);
		tmp = tmp->right;
		i++;
	}
	while(g_pid_list.amt > 0)
	{
		// ft_dprintf(STDOUT_FILENO, "removing process:\n");
		// vector_debug(STDOUT_FILENO, &g_pid_list, pid_print);
		int *this_one = vector_get(&g_pid_list, 0); //should make sure to wait for processes to finish in the right order, but also have processes remain open until not used anymore
		// ft_dprintf(STDOUT_FILENO, "pid to wait for: %d\n", *this_one);
		wait(this_one);
		free(this_one);
		vector_delete(&g_pid_list, 0);
		// ft_dprintf(STDOUT_FILENO, "\n\n");
	}
}
