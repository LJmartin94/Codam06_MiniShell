/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 11:32:10 by limartin      #+#    #+#                 */
/*   Updated: 2021/01/05 10:29:41 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include "libft.h"

/*
** TODO:
** Rework error reporting, probably shouldnt even exit the shell.
** Test with deleted directories, permission denied dirs.
*/

int			ft_pwd(t_vector *env, t_icomp *cmp, int fd)
{
	char *buf;

	(void)env;
	(void)cmp;
	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf == NULL)
		error_exit_errno();
	e_write(fd, buf, ft_strlen(buf));
	free(buf);
	e_write(fd, "\n", 1);
	return (0);
}
