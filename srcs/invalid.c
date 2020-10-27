/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   invalid.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:09:20 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/27 12:31:30 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "minishell.h"

// TODO: Redo this so error message is built in command?

void	invalid_cmd(t_icomp cmd)
{
	ft_dprintf(STDERR_FILENO, "Invalid command: '%s %s %s'\n", cmd.cmd, cmd.opt, cmd.arg);
	//TODO: stop program?
}