/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 11:32:10 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/01 22:07:17 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include "libft.h"

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
	e_write(STDIN_FILENO, buf, ft_strlen(buf));
	e_write(STDIN_FILENO, "\n", 1);
	return (0);
}

//./Users/limartin/Desktop/some/where/highly/specific/that/will/result/in/really/quite/a/long/path/name/if/one/was/hypothetically/to/test/whether/pwd/(/print/working/directory/)/was/working/for/the/purposes/of/ironing/out/edge/cases/in/mini/shell/
// /\/:/\n/000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000/untitled folder/cd/".."/ok it works I guess...

/*
** TODO: 
** Check if pwd commands still works normally in bash after PWD is unset from env
** Rework error reporting, probably shouldnt even exit the shell.
*/
