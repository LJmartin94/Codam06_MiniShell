/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 10:39:47 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/07 12:43:00 by jsaariko      ########   odam.nl         */
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
	t_redir *rd = comp->rdhead;

	redirect_pipes(comp, p_fd, stdin);
	while(rd != NULL)
	{	
		ft_dprintf(STDOUT_FILENO, "[%s]\n", rd->file);
		if (ft_strncmp(rd->type_out, ">>", 3) == 0)
			fd = open(rd->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else if (ft_strncmp(rd->type_out, ">", 2) == 0)
			fd = open(rd->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (ft_strncmp(rd->type_in, "<", 2) == 0)
		{
			fd = open(rd->file, O_RDONLY, 0666);
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
		rd = rd->right;
	}
}

/*
** //TODO: Solidify error checking
*/

int			redirect_builtin(t_icomp *comp)
{
	int fd;
	t_redir *rd = comp->rdhead;

	fd = STDOUT_FILENO;
	while(rd)
	{
		if (ft_strncmp(rd->type_out, ">>", 3) == 0)
			fd = open(rd->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else if (ft_strncmp(rd->type_out, ">", 2) == 0)
			fd = open(rd->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (ft_strncmp(rd->type_in, "<", 2) == 0)
		{
			fd = open(rd->file, O_RDONLY, 0666);
			if (fd == -1)
				ft_dprintf(STDERR_FILENO, "oops, no such file");
			else
				close(fd);
			fd = STDOUT_FILENO;
		}
		rd = rd->right;
	}
	return (fd);
}
