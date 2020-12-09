/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   invalid.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:09:20 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/09 14:26:23 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "execute.h"
#include "libft.h"

/*
** //TODO: if invalid_cmd, return value is 127
** // TODO: remove separate exit statements as invalid cmd exits now
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
	e_write(STDERR_FILENO, "shnell: ", 8);
	e_write(STDERR_FILENO, cmd->cmd, ft_strlen(cmd->cmd));
	e_write(STDERR_FILENO, ": ", 1);
	e_write(STDERR_FILENO, msg, ft_strlen(msg));
	e_write(STDERR_FILENO, "\n", 1);
}
