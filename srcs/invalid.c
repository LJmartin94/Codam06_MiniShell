/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   invalid.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:09:20 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/08 15:45:56 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "execute.h"
#include "libft.h"

//TODO: if invalid_cmd, return value is 127
// TODO: remove separate exit statements as invalid cmd exits now
void	invalid_cmd(t_icomp *cmd)
{
	ft_dprintf(STDERR_FILENO, "Invalid command: '%s %s %s'\n",
	cmd->cmd, cmd->opt, cmd->arg->value);
	g_ret_val = 127;
	exit(127);
}

/*
**  //TODO: maybe print cmd->arg as well
*/

void	cmd_error(t_icomp *cmd, char *msg, int fd)
{
	e_write(fd, "shnell: ", 8);
	e_write(fd, cmd->cmd, ft_strlen(cmd->cmd));
	e_write(fd, ": ", 1);
	e_write(fd, msg, ft_strlen(msg));
	e_write(fd, "\n", 1);
}
