/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:38:54 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/28 15:31:41 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include "libft.h"

/*
**  //TODO: Find valid error check
*/

int	validate_cmd_echo(t_icomp *cmd)
{
	if (cmd->opt == NULL)
		return (1);
	if (ft_strncmp(cmd->opt, "-n", 3) != 0)
		return (0);
	return (1);
}

/*
**  //TODO: get rid of line 37 etc, if parsing changes
*/

int	ft_echo(t_icomp *cmd)
{
	validate_cmd_echo(cmd);
	if (cmd->arg == NULL && cmd->opt == NULL)
	{
		e_write(STDIN_FILENO, "\n", 1);
		return (0);
	}
	if (cmd->arg != NULL)
		e_write(STDIN_FILENO, cmd->arg, ft_strlen(cmd->arg));
	if (cmd->opt == NULL)
		e_write(1, "\n", 1);
	else if (ft_strncmp(cmd->opt, "-n", 3) != 0)
		return (0);
	return (0);
}
