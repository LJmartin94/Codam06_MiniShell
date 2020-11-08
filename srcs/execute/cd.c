/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 13:26:26 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/08 18:21:49 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include "libft.h"

t_env	*find_env_kvp(t_vector *env, const char *key)
{
	size_t	i;
	t_env	*ret;

	i = 0;
	while (i < env->amt)
	{
		ret = (t_env *)vector_get(env, i);
		if (ft_strncmp(ret->key, key, ft_strlen(ret->key)) == 0 && \
			ft_strncmp(ret->key, key, ft_strlen(key)) == 0)
			break ;
		ret = NULL;
		i++;
	}
	return (ret);
}

static int	validate_cmd_cd(t_icomp *cmp)
{
	if (ft_strncmp(cmp->opt, "", 1) != 0)
		return (0);
	return (1);
}

static int	go_relative(t_vector *env, t_icomp *cmp)
{
	int dir;

	dir = 0;
	(void)env;
	(void)cmp;
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
	t_env	*home;

	path = "";
	home = find_env_kvp(env, "HOME");
	if (home != NULL)
		path = home->value;
	dir = chdir(path);
	if (dir == -1)
	{
		path = NULL;
		home = find_env_kvp(env, "USER");
		if (home != NULL)
			path = ft_strjoin("/Users/", home->value);
		if (path != NULL)
			dir = chdir(path);
		if (dir != -1)
			e_write(STDERR_FILENO, "HOME not properly set, using USER\n", 34);
		if (dir != -1 && path != NULL)
			free(path);
	}
	if (dir == -1)
		e_write(STDERR_FILENO, "HOME not properly set, staying put\n", 35);
	return (dir);
}

int			ft_cd(t_vector *env, t_icomp *cmp)
{
	//char	*cwd;
	int		dir;

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
	// cwd = NULL;
	// cwd = getcwd(cwd, 0);
	// if (cwd == NULL)
	// 	error_exit_errno();
	return (dir);
}

// cd /Users/limartin/Desktop/some/where/highly/specific/that/will/result/in/really/quite/a/long/path/name/if/one/was/hypothetically/to/test/whether/pwd/\(/print/working/directory/\)/was/working/for/the/purposes/of/ironing/out/edge/cases/in/mini/shell/\ /\\/:/\\n/000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000/untitled\ folder/cd/\"..\"/ok\ it\ works\ I\ guess...

/*
** TODO
** Also set PWD and OLDPWD in env. (OLDPWD is updated even if the same as PWD, so upon succesful directory change command)
** check .. and . work etc
*/
