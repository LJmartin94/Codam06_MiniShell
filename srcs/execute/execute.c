/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/28 15:14:40 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"

/*
** TODO: Build command validators in functions
*/

typedef int(*cmd)(t_icomp *);

cmd		get_command(t_icomp *comp)
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
	cmd f;

	f = get_command(comp);
	if (f != NULL)
		f(comp);
}
