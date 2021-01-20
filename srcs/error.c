/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/20 09:58:37 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/20 15:41:33 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include <unistd.h>
#include <errno.h>

void	*e_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
		error_exit_errno();
	ft_bzero(ptr, size);
	return (ptr);
}

void	e_write(int fd, const char *buf, size_t size)
{
	int ret;

	if (fd < 0)
		error_exit_msg(C_INVALID_FILE, E_INVALID_FILE);
	ret = write(fd, buf, size);
	if (ret == -1)
		exit(errno);
}

void	e_close(int fd)
{
	if (fd == -1)
		return ;
	if (close(fd) == -1)
	{
		e_write(STDOUT_FILENO, "e_close: ", 9);
		error_exit_errno();
	}
}

char	*e_strjoin(const char *s1, const char *s2)
{
	char	*new_val;

	new_val = ft_strjoin(s1, s2);
	if (new_val == NULL)
		error_exit_errno();
	return (new_val);
}

char	*e_strdup(char *str)
{
	char *new;

	new = ft_strdup(str);
	if (new == NULL)
		error_exit_errno();
	return (new);
}
