/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 14:28:00 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/03 14:05:51 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"


//TODO: make sure to check how it interacts with multiple args
//TODO: exit a seems to actually exit at codam with status 255??
int	ft_exit(t_vector *env, t_icomp *cmd, int fd)
{
	size_t	i;
	t_arg *arg = cmd->arg;

	i = 0;
	//if too many args, returns 1 and writes error msg too many args
	if (arg->right != NULL)
	{
		cmd_error(cmd, "Too many arguments\n", fd);//send error to fd?
		return (1); //Doesnt exit with this error
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
	(void)fd;
	exit(ft_atoi(cmd->arg->value));
}
