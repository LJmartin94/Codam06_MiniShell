/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:38:54 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/29 14:06:59 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include "libft.h"

int	ft_echo(t_vector *env, t_icomp *cmd)
{
	(void)env;
	e_write(STDIN_FILENO, cmd->arg, ft_strlen(cmd->arg));
	if (ft_strnstr(cmd->opt, "-n", ft_strlen(cmd->opt)) == NULL)
		e_write(STDIN_FILENO, "\n", 1);
	return (0);
}
