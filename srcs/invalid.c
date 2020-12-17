/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   invalid.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:09:20 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/17 15:56:56 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "execute.h"
#include "libft.h"
#include "parse.h"

/*
** //TODO: if invalid_cmd, return value is 127
** // TODO: remove separate exit statements as invalid cmd exits now
*/

void	invalid_cmd(t_icomp *cmd)
{
	ft_dprintf(STDERR_FILENO, "Invalid command: '%s %s %s'\n",
	cmd->cmd, cmd->opt, cmd->arg->value);
	g_ret_val = 127;
	exit(127);
}

/*
**  //TODO: maybe print cmd->arg as well
*/

void	cmd_error(t_icomp *cmd, char *msg, int fd)
{
	e_write(fd, "Minishnail: ", 12);
	e_write(fd, cmd->cmd, ft_strlen(cmd->cmd));
	e_write(fd, ": ", 1);
	e_write(fd, msg, ft_strlen(msg));
	e_write(fd, "\n", 1);
}

void	syntax_error(int fd, t_token **this)
{
	e_write(fd, "Minishnail: ", 12);
	e_write(fd, "syntax error near unexpected token `", 36);
	if (*this != NULL)
		e_write(fd, (*this)->token, ft_strlen((*this)->token));
	e_write(fd, "'\n", 2);
}

int		no_syntax_errors(t_icomp *head)
{
	t_icomp *current;

	current = head;
	while (current != NULL)
	{
		if (current->arg->type[0] == 'E')
			return (0);
		current = current->right;
	}
	return (1);
}
