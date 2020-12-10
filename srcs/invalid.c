/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   invalid.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:09:20 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/05 10:03:01 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "execute.h"
#include "libft.h"

/*
** //TODO: if invalid_cmd, return value is 127
*/

void	invalid_cmd(t_icomp *cmd)
{
	e_write(STDERR_FILENO, "Invalid command: ", 17);
	e_write(STDERR_FILENO, cmd->cmd, ft_strlen(cmd->cmd));
	e_write(STDERR_FILENO, "\n", 1);
	g_ret_val = 127;
	exit(127);
}

/*
**  //TODO: maybe print cmd->arg as well
*/

void	cmd_error(t_icomp *cmd, char *msg)
{
	e_write(STDERR_FILENO, "Minishnail: ", 12);
	e_write(STDERR_FILENO, cmd->cmd, ft_strlen(cmd->cmd));
	e_write(STDERR_FILENO, ": ", 2);
	e_write(STDERR_FILENO, msg, ft_strlen(msg));
	e_write(STDERR_FILENO, "\n", 1);
}
