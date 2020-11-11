/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   invalid.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:09:20 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/11 15:11:15 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "minishell.h"
#include "libft.h"

/*
** //TODO: stop program?
*/

void	invalid_cmd(t_icomp *cmd)
{
	ft_dprintf(STDERR_FILENO, "Invalid command: '%s %s %s'\n",
	cmd->cmd, cmd->opt, cmd->arg);
}

//TODO: pass argument when failed?
void	cmd_error(t_icomp *cmd, char *msg, int fd)
{
	e_write(fd, "shnell: ", 8);
	e_write(fd, cmd->cmd, ft_strlen(cmd->cmd));
	e_write(fd, ": ", 1); //TODO: maybe print cmd->arg as well
	e_write(fd, msg, ft_strlen(msg));
	e_write(fd, "\n", 1);
}