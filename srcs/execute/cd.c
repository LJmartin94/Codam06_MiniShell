/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 13:26:26 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/31 16:51:22 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include "libft.h"

static int	validate_cmd_cd(t_icomp *cmp)
{
	if (ft_strncmp(cmp->opt, "", 1) != 0)
		return (0);
	return (1);
}

static int 	go_relative(t_vector *env)
{
	(void)env;
	return (0);
}

static int	go_absolute(t_vector *env)
{
	(void)env;
	return (0);
}

static int	go_home(t_vector *env)
{
	int dir;

	(void)env;
	//try to use env to find what home is set to
	//else try to use env to find what the username is or perhaps logname, check if you can go to users/'username'
	//else try to go to users and see if you can find a dir you have the rights to access
	//else try to go to the second dir of current pwd
	//else just go to absolute root '/'
	dir = chdir("/");
	if (dir == -1)
		error_exit_errno();
	return (0);
}

int			ft_cd(t_vector *env, t_icomp *cmp)
{
	char *cwd;

	(void)env;
	if (validate_cmd_cd(cmp) == 0)
	{
		invalid_cmd(cmp);
		return (1);
	}
	if (ft_strncmp(cmp->arg, "", 1) != 0)
		return (go_home(env));
	else if (ft_strncmp(cmp->arg, "/", 1) != 0)
		return (go_absolute(env));
	else
		return (go_relative(env));
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
		error_exit_errno();
	return (0);
}

// cd /Users/limartin/Desktop/some/where/highly/specific/that/will/result/in/really/quite/a/long/path/name/if/one/was/hypothetically/to/test/whether/pwd/\(/print/working/directory/\)/was/working/for/the/purposes/of/ironing/out/edge/cases/in/mini/shell/\ /\\/:/\\n/000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000/untitled\ folder/cd/\"..\"/ok\ it\ works\ I\ guess...