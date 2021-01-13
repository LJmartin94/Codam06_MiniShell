/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   invalid.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:09:20 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/13 19:35:48 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "execute.h"
#include "libft.h"
#include "parse.h"

void	invalid_cmd(t_icomp *cmd)
{
	e_write(STDERR_FILENO, "Invalid command: ", 17);
	e_write(STDERR_FILENO, cmd->cmd, ft_strlen(cmd->cmd));
	e_write(STDERR_FILENO, "\n", 1);
	g_ret_val = 127;
	exit(127);
}

void	cmd_error(t_icomp *cmd, char *msg)
{
	e_write(STDERR_FILENO, "Minishnail: ", 12);
	e_write(STDERR_FILENO, cmd->cmd, ft_strlen(cmd->cmd));
	e_write(STDERR_FILENO, ": ", 2);
	e_write(STDERR_FILENO, msg, ft_strlen(msg));
	e_write(STDERR_FILENO, "\n", 1);
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
