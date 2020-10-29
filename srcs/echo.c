/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:38:54 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/27 10:51:22 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

int	validate_cmd_echo(t_icomp cmd)
{
	if (cmd.opt == NULL)
		return (1);
	if (ft_strncmp(cmd.opt, "-n", 3) != 0) //TODO: Find valid error check
		return (0);
	return (1);
}

int	ft_echo(t_vector *env, t_icomp cmd)
{
	(void)env;
	validate_cmd_echo(cmd);
	if (cmd.arg == NULL && cmd.opt == NULL) //TODO: get rid of this if parsing changes
	{
		e_write(STDIN_FILENO, "\n", 1);
		return (0);
	}
	e_write(STDIN_FILENO, cmd.arg, ft_strlen(cmd.arg));
	if (cmd.opt == NULL)
		e_write(1, "\n", 1);
	else if (ft_strncmp(cmd.opt, "-n", 3) != 0)
		return (0);
	return (0);
}