/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 14:28:00 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/27 16:55:20 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"


//TODO: make sure to check how it interacts with multiple args
int	ft_exit(t_vector *env, t_icomp *cmd, int fd)
{
	size_t	i;

	i = 0;
	if (cmd->arg->value[i] == '\0')
		exit(g_ret_val);
	while (cmd->arg->value[i] != '\0')
	{
		if (!ft_isdigit(cmd->arg->value[i]))
		{
			cmd_error(cmd, "numeric argument required", STDERR_FILENO);
			exit(255);
		}
		i++;
	}
	(void)env;
	(void)fd;
	exit(ft_atoi(cmd->arg->value));
}
