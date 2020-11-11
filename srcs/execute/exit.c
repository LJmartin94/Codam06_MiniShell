/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 14:28:00 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/11 15:10:04 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//TODO: If numeric param provided, exits with said param
//TODO: If not, exits with exit code of last command (g_ret_val)
//TODO: what if non numeric param provided? errors, still exits, but what exit value?

int	ft_exit(t_vector *env, t_icomp *cmd, int fd) 
{
	(void)env;
	(void)fd;
	size_t i;
	i = 0;
	// int ret; //TODO: Maybe unsigned char?
	// if (cmd->arg[0] == '\0')
		// exit(g_ret_val);
	while (cmd->arg[i] != '\0')
	{
		if (!ft_isdigit(cmd->arg[i]))
		{
			cmd_error(cmd, "numeric argument required", STDERR_FILENO);
			exit(255);
		}
		i++;
	}
	exit(ft_atoi(cmd->arg));
}
