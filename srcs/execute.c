/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/27 12:36:53 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
** TODO: Build command validators in functions
*/

typedef int(*cmd)(t_vector *, t_icomp);

cmd		get_command(t_icomp comp)
{
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
	if (ft_strncmp(comp.cmd, "cd", 2) == 0)
		return (ft_cd);
	if (ft_strncmp(comp.cmd, "exit", 2) == 0)
		return (ft_exit);
	return (NULL);
}

void	execute(t_vector *env, t_icomp comp)
{
	cmd f;

	f = get_command(comp);
	if (f == NULL)
		invalid_cmd(comp);
	else
		f(env, comp);
}
