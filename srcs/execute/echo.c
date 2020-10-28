/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:38:54 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/28 17:32:14 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include "libft.h"

// int	validate_cmd_echo(t_icomp *cmd)
// {
// 	if (cmd->opt != '\0' || ft_strncmp(cmd->opt, "-n", 3) != 0)
// 		return (0);
// 	return (1);
// }

int	ft_echo(t_icomp *cmd)
{
	// if (validate_cmd_echo(cmd) == 1)
	// {
	// 	invalid_cmd(cmd);
	// 	return (0);
	// }
	e_write(STDIN_FILENO, cmd->arg, ft_strlen(cmd->arg));
	if (ft_strncmp(cmd->opt, "-n", 3) != 0)
		e_write(STDIN_FILENO, "\n", 1);
	return (0);
}
