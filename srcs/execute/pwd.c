/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 11:32:10 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/11 16:14:12 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include "libft.h"

/*
** TODO:
** Rework error reporting, probably shouldnt even exit the shell.
*/

static int	validate_cmd_pwd(t_icomp *cmp)
{
	if (ft_strncmp(cmp->arg, "", 1) != 0 || ft_strncmp(cmp->opt, "", 1) != 0)
		return (0);
	return (1);
}

int			ft_pwd(t_vector *env, t_icomp *cmp)
{
	char *buf;

	(void)env;
	if (validate_cmd_pwd(cmp) == 0)
	{
		invalid_cmd(cmp);
		return (1);
	}
	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf == NULL)
		error_exit_errno();
	e_write(STDOUT_FILENO, buf, ft_strlen(buf));
	e_write(STDOUT_FILENO, "\n", 1);
	return (0);
}
