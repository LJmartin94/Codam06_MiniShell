/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 13:26:26 by limartin      #+#    #+#                 */
/*   Updated: 2021/01/11 15:24:26 by jsaariko      ########   odam.nl         */
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
** Fix Memleaks
*/


//TODO: set global pwd on function entrance
//TODO: always reset g_pwd on cd
//TODO: g_pwd should not be related to env
//TODO: if getcwd doesn't work, I should use g_pwd instead to find my path and add shit onto it


void update_pwd(t_vector *env)
{
	t_env *env_path;
	char *cwd;

	cwd = NULL;
	env_path = vector_get(env, vector_search(env, compare_key, (void *)"PWD"));
	free(env_path->value);
	cwd = getcwd(cwd, 0);
	env_path->value = ft_strdup(cwd);//this needs to change
	free(g_pwd);
	g_pwd = ft_strdup(cwd);//have to strdup this
}

int			escape_being_lost(t_vector *env, char *path)
{
	char **split;
	int i;
	int len;

	i = 0;
	split = ft_split(path, '/');
	while (split[i] != NULL)
	{
		// if (split[i + 1] == NULL)
		if (split[i + 1] == NULL && ft_strncmp(split[i], "..", 3) == 0 )
		{
			len = ft_strlen(split[i - 1]) + 4;
			path[ft_strlen(path) - len] = '\0';
			int dir = chdir(path);
			if (dir == -1)
			{
				// printf("g_pwd: %s, path: %s\n", g_pwd, path);
				break ;
			}
			else
			{
				update_pwd(env);
				// free(path);
				// free_matrix(split);
				return(0);				
			}
		}
		i++;
	}
	e_write(STDERR_FILENO, "Could not access ", 17);
	e_write(STDERR_FILENO, path, ft_strlen(path));
	e_write(STDERR_FILENO, "\n", 1);
	g_pwd = ft_strdup(path);
	t_env *item = vector_get(env, vector_search(env, compare_key, (void *)"PWD"));
	item->value = ft_strdup(path);
	//env = path;
	// free(path);
	return(1);
}

static int	go_relative(t_vector *env, char *arg_str)
{
	int		dir;
	char	*cwd;
	char	*path;

	(void)env;
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
	{
		e_write(STDERR_FILENO, "No such file or directory\n", 27);//TODO: change
		cwd = g_pwd;
	}
	path = ft_strjoin(cwd, "/");
	free(cwd);
	cwd = path;
	path = (path != NULL) ? ft_strjoin(cwd, arg_str) : NULL;
	free(cwd);
	if (path == NULL)
		ft_dprintf(STDOUT_FILENO, "Path is NULL (this shouldn't happen)\n");
	dir = chdir(path);
	if (dir == -1)
		return(escape_being_lost(env, path));
	// g_pwd = path;
	// if (dir == -1)
	// {
		// e_write(STDERR_FILENO, "Could not access ", 17);
		// e_write(STDERR_FILENO, path, ft_strlen(path));
		// e_write(STDERR_FILENO, "\n", 1);
		// return (1);
	// }
	// update_pwd(env);
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
	free(g_pwd);
	// g_pwd = path;
	if (dir == -1)
	{
		e_write(STDERR_FILENO, "Could not access ", 17);
		e_write(STDERR_FILENO, path, ft_strlen(path));
		e_write(STDERR_FILENO, "\n", 1);
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
	free(g_pwd);
	// g_pwd = path;
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
