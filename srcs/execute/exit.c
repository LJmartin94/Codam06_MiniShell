/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 14:28:00 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/10 10:31:29 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	ft_exit(t_vector *env, t_icomp *cmd, int fd)
{
	// int ret;

	(void)env;
	(void)cmd;
	(void)fd;
	// if (cmd->arg)//TODO: if not numeric
	// {
		// ft_dprintf(STDOUT_FILENO, "");
		// ret = 255;
	// }
	// if (ft_strncmp(cmd->arg, "", 1))
		// ret = g_ret_val;
	// else
	// ret = ft_atoi(cmd->arg);
	exit(0);
}
