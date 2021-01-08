/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 11:32:10 by limartin      #+#    #+#                 */
/*   Updated: 2021/01/08 19:34:23 by jsaariko      ########   odam.nl         */
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

int search_cmp(char *s1, char *s2)
{
	int len = 0;
	if (ft_strlen(s2) > ft_strlen(s1))
		len = ft_strlen(s2) + 1;
	else
		len = ft_strlen(s1) + 1;
	if (ft_strncmp(s1, s2, len) == 0)
		return (0);
	else
		return (1);
}

int			ft_pwd(t_vector *env, t_icomp *cmp, int fd)
{
	char *buf;

	(void)env;
	(void)cmp;
	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf == NULL)
	{
		ft_dprintf(STDOUT_FILENO, "lol\n");//
		e_write(fd, g_pwd, ft_strlen(g_pwd));
		e_write(fd, "\n", 1);
		return (0);
	}
	e_write(fd, buf, ft_strlen(buf));
	free(buf);
	e_write(fd, "\n", 1);
	return (0);
}
