/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 10:39:47 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/04 18:48:01 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include <fcntl.h>
#include <unistd.h>

/*
** //TODO: change error handling
** //Redirections seem to commonly exit with status 13??
*/

static void	redirect_pipes(t_icomp *comp, int p_fd[2], int stdin)
{
	if (stdin != -1)
	{
		dup2(stdin, STDIN_FILENO);
		e_close(stdin);
	}
	if (ft_strncmp(comp->sep, "|", 2) == 0)
	{
		dup2(p_fd[1], STDOUT_FILENO);
		e_close(p_fd[0]);
		e_close(p_fd[1]);
	}
}

void		handle_redirections(t_icomp *comp, int p_fd[2], int stdin)
{
	int fd;

	redirect_pipes(comp, p_fd, stdin);
	if (ft_strncmp(comp->rdhead->type_out, ">>", 3) == 0)
		fd = open(comp->rdhead->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (ft_strncmp(comp->rdhead->type_out, ">", 2) == 0)
		fd = open(comp->rdhead->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (ft_strncmp(comp->rdhead->type_in, "<", 2) == 0)
	{
		fd = open(comp->right->cmd, O_RDONLY, 0666);
		if (fd == -1)
		{
			ft_dprintf(STDERR_FILENO, "oops, no such file\n");
			exit(0);
		}
		dup2(fd, STDIN_FILENO);
		e_close(fd);
		return ;
	}
	else
		return ;
	dup2(fd, STDOUT_FILENO);
	e_close(fd);
}

/*
** //TODO: Solidify error checking
*/

int			redirect_builtin(t_icomp *comp)
{
	int fd;

	fd = STDOUT_FILENO;
	if (ft_strncmp(comp->sep, ">>", 3) == 0)
		fd = open(comp->right->cmd, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (ft_strncmp(comp->sep, ">", 2) == 0)
		fd = open(comp->right->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (ft_strncmp(comp->sep, "<", 2) == 0)
	{
		fd = open(comp->right->cmd, O_RDONLY, 0666);
		if (fd == -1)
			ft_dprintf(STDERR_FILENO, "oops, no such file");
		else
			close(fd);
		fd = STDOUT_FILENO;
	}
	return (fd);
}
