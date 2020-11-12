/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 13:26:26 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/12 14:01:28 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include "libft.h"

/*
** TODO
** Also set PWD and OLDPWD in env. '
** (OLDPWD is updated even if the same as PWD,
** so upon succesful directory change command)
** Check return values are correct for pwd and cd?
** Test with deleted directories, permission denied dirs.
*/

static int	validate_cmd_cd(t_icomp *cmp)
{
	if (ft_strncmp(cmp->opt, "", 1) != 0)
		return (0);
	return (1);
}

static int	go_relative(t_vector *env, t_icomp *cmp)
{
	int		dir;
	char	*cwd;
	char	*path;

	(void)env;
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
		error_exit_errno();
	path = ft_strjoin(cwd, "/");
	if (path != NULL)
		path = ft_strjoin(path, cmp->arg);
	if (path == NULL)
		error_exit_errno();
	dir = chdir(path);
	if (dir == -1)
	{
		e_write(STDERR_FILENO, "Could not access ", 17);
		e_write(STDERR_FILENO, path, ft_strlen(path));
		e_write(STDERR_FILENO, "\n", 1);
	}
	return (dir);
}

static int	go_absolute(t_vector *env, t_icomp *cmp)
{
	int		dir;
	char	*path;

	(void)env;
	path = cmp->arg;
	dir = chdir(path);
	if (dir == -1)
	{
		e_write(STDERR_FILENO, "Could not access ", 17);
		e_write(STDERR_FILENO, path, ft_strlen(path));
		e_write(STDERR_FILENO, "\n", 1);
	}
	return (dir);
}

static int	go_home(t_vector *env)
{
	int		dir;
	char	*path;
	int		index;
	t_env	*home;

	path = "";
	home = NULL;
	index = vector_search(env, compare_key, (void *)"HOME");
	if (index >= 0)
		home = vector_get(env, index);
	if (home != NULL)
		path = home->value;
	dir = chdir(path);
	if (dir == -1)
		e_write(STDERR_FILENO, "HOME not properly set, staying put\n", 35);
	return (dir);
}

int			ft_cd(t_vector *env, t_icomp *cmp, int fd)
{
	int		dir;

	(void)fd;
	(void)env;
	dir = 0;
	if (validate_cmd_cd(cmp) == 0)
	{
		invalid_cmd(cmp);
		return (1);
	}
	if (ft_strncmp(cmp->arg, "", 1) == 0)
		dir = go_home(env);
	else if (ft_strncmp(cmp->arg, "/", 1) == 0)
		dir = go_absolute(env, cmp);
	else
		dir = go_relative(env, cmp);
	return (dir);
}
