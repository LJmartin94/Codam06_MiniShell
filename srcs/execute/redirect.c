/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 10:39:47 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/14 16:07:52 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include <fcntl.h>
#include <unistd.h>

static void	redirect_pipes(t_icomp *comp, int p_fd[2], t_vector *fd_list)
{
	int *input;

	input = vector_get(fd_list, fd_list->amt - 1);
	if (!(fd_list->amt == 0 || *input == -1))
	{
		dup2(*input, STDIN_FILENO);
		e_close(*input);
	}
	if (ft_strncmp(comp->sep, "|", 2) == 0)
	{
		dup2(p_fd[1], STDOUT_FILENO);
		e_close(p_fd[0]);
		e_close(p_fd[1]);
	}
}

static int	redirect_to(const char *rd, const char *file)
{
	int fd;

	fd = -1;
	if (ft_strncmp(rd, ">>", 3) == 0)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
			error_exit_errno();
	}
	else if (ft_strncmp(rd, ">", 2) == 0)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			error_exit_errno();
	}
	return (fd);
}

void		handle_redirections(t_icomp *comp, int p_fd[2],
				t_vector *fd_list)
{
	int		fd;
	t_redir	*rd;

	rd = comp->rdhead;
	redirect_pipes(comp, p_fd, fd_list);
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
				error_exit_msg(1, "Oops, no such file");
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
		if (ft_strncmp(rd->type_out, ">", 1) == 0)
			fd = redirect_to(rd->type_out, rd->file);
		else if (ft_strncmp(rd->type_in, "<", 2) == 0)
		{
			fd = open(rd->file, O_RDONLY, 0666);
			if (fd == -1)
				e_write(STDERR_FILENO, "Oops, no such file or directory", 32);
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
