/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 10:39:47 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/08 09:47:55 by jsaariko      ########   odam.nl         */
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

/*
** //TODO: exit status for when file not found on < is 1 ???
*/

int			redirect_to(const char *rd, const char *file)
{
	int fd;

	fd = -1;
	if (ft_strncmp(rd, ">>", 3) == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (ft_strncmp(rd, ">", 2) == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	return (fd);
}

/*
** //TODO: Solidify error checking
*/

void		handle_redirections(t_icomp *comp, int p_fd[2], int stdin)
{
	int		fd;
	t_redir	*rd;

	rd = comp->rdhead;
	redirect_pipes(comp, p_fd, stdin);
	while (rd != NULL)
	{
		if (ft_strncmp(rd->type_out, ">", 1) == 0)
		{
			fd = redirect_to(rd->type_out, rd->file);
			dup2(fd, STDOUT_FILENO);
			e_close(fd);
		}
		else if (ft_strncmp(rd->type_in, "<", 2) == 0)
		{
			fd = open(rd->file, O_RDONLY, 0666);
			if (fd == -1)
				error_exit_msg(1, "oops, no such file");
			dup2(fd, STDIN_FILENO);
			e_close(fd);
		}
		rd = rd->right;
	}
}

int			redirect_builtin(t_icomp *comp)
{
	int		fd;
	t_redir	*rd;

	rd = comp->rdhead;
	fd = -1;
	while (rd)
	{
		if (fd != -1)
			e_close(fd);
		if (ft_strncmp(rd->type_out, ">", 1) == 0)
			fd = redirect_to(rd->type_out, rd->file);
		else if (ft_strncmp(rd->type_in, "<", 2) == 0)
		{
			fd = open(rd->file, O_RDONLY, 0666);
			if (fd == -1)
				ft_dprintf(STDERR_FILENO, "oops, no such file");
			else
				e_close(fd);
			fd = STDOUT_FILENO;
		}
		rd = rd->right;
	}
	if (fd == -1)
		fd = STDOUT_FILENO;
	return (fd);
}
