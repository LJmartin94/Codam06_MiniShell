/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/20 09:58:37 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/21 16:29:16 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include <string.h>
#include <unistd.h>
#include <errno.h>

void	error_exit_msg(const unsigned int e_code, const char *e_msg)
{
	char *err_num;

	err_num = ft_itoa(e_code);
	if (!err_num)
		exit(errno);
	e_write(STDERR_FILENO, "Error\nMinishell(", 16);
	e_write(STDERR_FILENO, err_num, ft_strlen(err_num));
	e_write(STDERR_FILENO, "): ", 3);
	e_write(STDERR_FILENO, e_msg, ft_strlen(e_msg));
	e_write(STDERR_FILENO, "\n", 1);
	exit(e_code);
}

void	error_exit_errno(void)
{
	char *errorstr;

	errorstr = strerror(errno);
	e_write(STDERR_FILENO, errorstr, ft_strlen(errorstr));
	e_write(STDERR_FILENO, "\n", 1);
	exit(errno);
}

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
