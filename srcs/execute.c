/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/27 16:49:34 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
** TODO: Build command validators in functions
*/

typedef int(*cmd)(t_vector *, t_icomp);

cmd		get_command(t_icomp comp)
{
	if (comp.cmd == NULL)
		return (NULL);
	if (ft_strncmp(comp.cmd, "env", 4) == 0)
		return (ft_env);
	if (ft_strncmp(comp.cmd, "unset", 6) == 0)
		return (ft_unset);
	if (ft_strncmp(comp.cmd, "export", 7) == 0)
		return (ft_export);
	if (ft_strncmp(comp.cmd, "echo", 5) == 0)
		return (ft_echo);
	if (ft_strncmp(comp.cmd, "pwd", 4) == 0)
		return (ft_pwd);
	if (ft_strncmp(comp.cmd, "cd", 3) == 0)
		return (ft_cd);
	if (ft_strncmp(comp.cmd, "exit", 5) == 0)
		return (ft_exit);
	ft_dprintf(STDIN_FILENO, "lol\n");
	return (NULL);
}

void	execute(t_vector *env, t_icomp comp)
{
	cmd f;


	//Iterate through items. If pipe, open pipe, fork command and write result from one process, read from other. Same with redirections. Always add process to g_pid
	f = get_command(comp);
	if (f == NULL)
		invalid_cmd(comp);
	else
		f(env, comp);
}
