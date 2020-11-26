/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:38:54 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/26 20:53:14 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include "libft.h"

int	ft_echo(t_vector *env, t_icomp *cmd)
{
	t_arg	*argument_link;

	(void)env;
	argument_link = cmd->arg;
	while (argument_link)
	{
		e_write(STDOUT_FILENO, argument_link->value, \
		ft_strlen(argument_link->value));
		e_write(STDOUT_FILENO, argument_link->pad, \
		ft_strlen(argument_link->pad));
		argument_link = argument_link->right;
	}
	if (ft_strnstr(cmd->opt, "-n", ft_strlen(cmd->opt)) == NULL)
		e_write(STDOUT_FILENO, "\n", 1);
	return (0);
}
