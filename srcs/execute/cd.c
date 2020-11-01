/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 13:26:26 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/01 21:10:17 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include "libft.h"

// int		write_kvp(int fd, t_env *kvp)
// {
// 	e_write(fd, kvp->key, ft_strlen(kvp->key));
// 	e_write(fd, "=", 1);
// 	e_write(fd, kvp->value, ft_strlen(kvp->value));
// 	e_write(fd, "\n", 1);
// 	return (0);
// }

// int		vector_print(int fd, t_vector *v, int (*print)())
// {
// 	size_t	i;
// 	int		ret;

// 	i = 0;
// 	ret = 0;
// 	while (i < v->amt && ret > -1)
// 	{
// 		if (ret > -1)
// 			print(fd, v->data[i]);
// 		ret = (ret > -1) ? write(fd, "\n", 0) : ret;
// 		i++;
// 	}
// 	return (ret);
// }

// int		vector_debug(int fd, t_vector *v, int (*print)())
// {
// 	int ret;

// 	ret = write(fd, "Number of items:		", 18);
// 	ft_putnbr_fd(v->amt, fd);
// 	ret = (ret > -1) ? write(fd, "\nItem size:			", 15) : ret;
// 	ft_putnbr_fd(v->item_size, fd);
// 	ret = (ret > -1) ? write(fd, "\nTotal size:			", 16) : ret;
// 	ft_putnbr_fd((v->amt * v->item_size), fd);
// 	ret = (ret > -1) ? write(fd, "\n", 1) : ret;
// 	if (ret > -1)
// 		ret = vector_print(fd, v, print);
// 	return (ret);
// }

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

t_env	*find_env_kvp(t_vector *env, const char *key)
{
	size_t	i;
	t_env	*ret;
	i = 0;
	while (i < env->amt)
	{
		ret = (t_env *)vector_get(env, i);
		if (ft_strncmp(ret->key, key, ft_strlen(ret->key)) == 0 && \
			ft_strncmp(ret->key, key, ft_strlen(key)) == 0 )
			break;
		ret = NULL;
		i++;
	}
	return (ret);
}

static int	go_home(t_vector *env)
{
	int		dir;
	char	*path;
	t_env	*home;

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
			e_write(STDIN_FILENO, "HOME not properly set, using USER\n", 34);
		if (dir != -1 && path != NULL)
			free(path);
	}
	if (dir == -1)
		e_write(STDIN_FILENO, "HOME not properly set, staying put\n", 35);
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
	if (ft_strncmp(cmp->arg, "", 1) == 0)
		go_home(env);
	else if (ft_strncmp(cmp->arg, "/", 1) == 0)
		go_absolute(env);
	else
		go_relative(env);
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
		error_exit_errno();
	return (0);
}

// cd /Users/limartin/Desktop/some/where/highly/specific/that/will/result/in/really/quite/a/long/path/name/if/one/was/hypothetically/to/test/whether/pwd/\(/print/working/directory/\)/was/working/for/the/purposes/of/ironing/out/edge/cases/in/mini/shell/\ /\\/:/\\n/000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000/untitled\ folder/cd/\"..\"/ok\ it\ works\ I\ guess...

/*
** Also set PWD and OLDPWD in env.
*/
