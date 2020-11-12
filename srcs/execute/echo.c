/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:38:54 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/12 13:57:32 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include "libft.h"

int	ft_echo(t_vector *env, t_icomp *cmd, int fd) //TODO: returns 0 unless write error
{
	(void)env;
	e_write(fd, cmd->arg, ft_strlen(cmd->arg));
	if (ft_strnstr(cmd->opt, "-n", ft_strlen(cmd->opt)) == NULL)
		e_write(fd, "\n", 1);
	return (0);
}
