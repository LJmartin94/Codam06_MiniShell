/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_exit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 14:13:08 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/07 14:14:34 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>

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
