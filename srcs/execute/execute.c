/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/17 15:40:31 by jsaariko      ########   odam.nl         */
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

/*
** //TODO: confirm that pid is handled correctly and kill pid_list
*/

void	execute(t_vector *env, t_icomp *comp)
{
	t_icomp	*tmp;
	int		stdin;

	vector_init(&g_pid_list);
	tmp = comp;
	stdin = -1;
	while (tmp != NULL)
	{
		stdin = exec_command(env, tmp, stdin);
		tmp = tmp->right;
	}
	if (g_pid_list.amt == 0)
		free(g_pid_list.data);
	else
		ft_dprintf(STDOUT_FILENO, "something wrong with pid_list\n");
}
