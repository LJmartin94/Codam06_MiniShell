/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 14:28:00 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/13 13:59:27 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	ft_exit(t_vector *env, t_icomp *cmd, int fd) 
{
	size_t	i;
	
	i = 0;
	if (cmd->arg[i] == '\0')
		exit(g_ret_val);
	while (cmd->arg[i] != '\0')
	{
		if (!ft_isdigit(cmd->arg[i]))
		{
			cmd_error(cmd, "numeric argument required", STDERR_FILENO);
			exit(255);
		}
		i++;
	}
	(void)env;
	(void)fd;
	exit(ft_atoi(cmd->arg));
}
