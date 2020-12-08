/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 14:28:00 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/07 14:45:14 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
** //TODO: make sure to check how it interacts with multiple args
** //TODO: exit a seems to actually exit at codam with status 255??
** //if too many args, returns 1 and writes error msg too many args
** //send error to fd or stderr?
** //What error code when exiting due to too many args
*/

int	ft_exit(t_vector *env, t_icomp *cmd, int fd)
{
	size_t	i;
	t_arg	*arg;

	i = 0;
	arg = cmd->arg;
	if (arg->right != NULL)
	{
		cmd_error(cmd, "Too many arguments\n", fd);
		return (1);
	}
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
	exit(ft_atoi(cmd->arg->value));
}
