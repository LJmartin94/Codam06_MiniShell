/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/28 16:56:06 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"

/*
** TODO: Build command validators in functions
*/

t_cmd	get_command(t_icomp *comp)
{
	if (comp->cmd == NULL)
		return (NULL);
	if (ft_strncmp(comp->cmd, "echo", 5) == 0)
		return (ft_echo);
	invalid_cmd(comp);
	return (NULL);
}

void	execute(t_icomp *comp)
{
	t_cmd	f;
	t_icomp	*tmp;

	tmp = comp;
	while (tmp != NULL)
	{
		// ft_dprintf(STDIN_FILENO, "cur command: %s\nnext addr: %p\n", tmp->cmd, tmp->right);
		f = get_command(tmp);
		f(tmp);
		tmp = tmp->right;
	}
}
