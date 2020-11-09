/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 10:39:47 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/06 11:53:20 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include <fcntl.h>
#include <unistd.h>

void	handle_redirections(t_icomp *comp, int p_fd[2])
{
	int fd;

	if (ft_strncmp(comp->sep, ">>", 3) == 0)
		fd = open(comp->right->cmd, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (ft_strncmp(comp->sep, ">", 2) == 0)
		fd = open(comp->right->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (ft_strncmp(comp->sep, "<", 2) == 0)
	{
		fd = open(comp->right->cmd, O_RDONLY, 0666);
		if (fd == -1)
		{
			//TODO: change error handling
			ft_dprintf(STDERR_FILENO, "oops, no such file\n");
			exit(0);
		}
		dup2(fd, STDIN_FILENO);
		e_close(fd);
		return ;
	}
	else if (ft_strncmp(comp->sep, "|", 2) == 0)
	{
		dup2(p_fd[1], STDOUT_FILENO);
		e_close(p_fd[0]);
		e_close(p_fd[1]);
		return ;
	}
	else
		return ;
	dup2(fd, STDOUT_FILENO);
	e_close(fd);
}
