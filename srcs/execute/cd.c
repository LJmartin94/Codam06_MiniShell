/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 13:26:26 by limartin      #+#    #+#                 */
/*   Updated: 2021/01/13 13:53:44 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include "cd.h"

/*
** TODO
** Also set PWD and OLDPWD in env. '
** (OLDPWD is updated even if the same as PWD,
** so upon succesful directory change command)
** Check return values are correct for pwd and cd?
** Test with deleted directories, permission denied dirs.
** Fix Memleaks
*/

//TODO: set oldpwd

static int	go_relative(t_vector *env, char *arg_str)
{
	int		dir;
	char	*cwd;
	char	*path;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
	{
		e_write(STDERR_FILENO, "No such file or directory\n", 27);//TODO: change
		cwd = ft_strdup(g_pwd);
	}
	path = ft_strjoin(cwd, "/");
	free(cwd);
	cwd = path;
	path = (path != NULL) ? ft_strjoin(cwd, arg_str) : NULL;
	free(cwd);
	if (path == NULL)
		error_exit_errno();
	dir = chdir(path);
	if (dir == -1)
		return(escape_being_lost(env, path));
	update_pwd(env);
	free(path);
	return (dir);
}

static int	go_absolute(t_vector *env, char *arg_str)
{
	int		dir;
	char	*path;

	(void)env;
	path = arg_str;
	dir = chdir(path);
	if (dir == -1)
	{
		cd_error(path);
		return (1);
	}
	update_pwd(env);
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
	{
		e_write(STDERR_FILENO, "HOME not properly set, staying put\n", 35);//TODO: run through error cmd
		return (1);
	}
	update_pwd(env);
	return (dir);
}

char		*get_arg_as_string(t_icomp *cmp)
{
	char	*arg_str;
	char	*newval;
	t_arg	*argument_link;

	arg_str = ft_strdup("");
	if (arg_str == NULL)
		error_exit_errno();
	argument_link = cmp->arg;
	while (argument_link)
	{
		newval = e_strjoin(arg_str, argument_link->value);
		free(arg_str);
		arg_str = newval;
		argument_link = (ft_strlen(argument_link->pad) > 0) ? \
		NULL : argument_link->right;
	}
	return (arg_str);
}

int			ft_cd(t_vector *env, t_icomp *cmp, int fd)
{
	int		dir;
	char	*arg_str;

	(void)fd;
	(void)env;
	dir = 0;
	arg_str = get_arg_as_string(cmp);
	if (ft_strncmp(arg_str, "", 1) == 0)
		dir = go_home(env);
	else if (ft_strncmp(arg_str, "/", 1) == 0)
		dir = go_absolute(env, arg_str);
	else
		dir = go_relative(env, arg_str);
	free(arg_str);
	return (dir);
}
