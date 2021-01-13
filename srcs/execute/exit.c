/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 14:28:00 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/13 19:24:50 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	ft_exit(t_vector *env, t_icomp *cmd, int fd)
{
	size_t	i;
	t_arg	*arg;

	i = 0;
	arg = cmd->arg;
	if (cmd->arg->value[i] == '\0')
		exit(g_ret_val);
	while (cmd->arg->value[i] != '\0')
	{
		if (!ft_isdigit(cmd->arg->value[i]))
		{
			cmd_error(cmd, "numeric argument required");
			exit(255);
		}
		i++;
	}
	if (arg->right != NULL)
	{
		cmd_error(cmd, "Too many arguments");
		return (1);
	}
	(void)env;
	(void)fd;
	exit(ft_atoi(cmd->arg->value));
}
