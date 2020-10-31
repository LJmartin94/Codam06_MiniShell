/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/31 16:23:12 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"

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
	if (ft_strncmp(comp->cmd, "pwd", 4) == 0)
		return (ft_pwd);
	if (ft_strncmp(comp->cmd, "cd", 4) == 0)
		return (ft_cd);
	return (NULL);
}

void	execute(t_vector *env, t_icomp *comp)
{
	t_cmd	f;
	t_icomp	*tmp;

	tmp = comp;
	while (tmp != NULL)
	{
		f = get_command(tmp);
		if (f == NULL)
			invalid_cmd(tmp);
		else
			f(env, tmp);
		tmp = tmp->right;
	}
}
