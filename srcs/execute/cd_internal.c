/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_internal.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 13:50:48 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/20 15:34:56 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execute.h"
#include "error.h"

void	update_pwd(t_vector *env)
{
	t_env	*tmp;
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	tmp = vector_get(env, vector_search(env, compare_key, (void *)"PWD"));
	if (tmp != NULL)
	{
		free(tmp->value);
		tmp->value = e_strdup(cwd);
	}
	tmp = vector_get(env, vector_search(env, compare_key, (void *)"OLDPWD"));
	if (tmp != NULL)
	{
		free(tmp->value);
		tmp->value = e_strdup(g_pwd);
	}
	free(g_pwd);
	g_pwd = cwd;
}

void	cd_error(char *path)
{
	e_write(STDERR_FILENO, "Could not access ", 17);
	e_write(STDERR_FILENO, path, ft_strlen(path));
	e_write(STDERR_FILENO, "\n", 1);
}

int		find_valid_dir(char **split, char *path, int i)
{
	int len;
	int dir;

	len = ft_strlen(split[i - 1]) + 4;
	ft_bzero(path + ft_strlen(path) - len, len);
	dir = chdir(path);
	if (dir == -1)
		return (-1);
	else
		return (0);
}

int		escape_being_lost(t_vector *env, char *path)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(path, '/');
	while (split[i] != NULL)
	{
		if (split[i + 1] == NULL && ft_strncmp(split[i], "..", 3) == 0)
		{
			if (find_valid_dir(split, path, i) == -1)
				break ;
			else
			{
				update_pwd(env);
				free_matrix(split);
				return (0);
			}
		}
		i++;
	}
	free_matrix(split);
	cd_error(path);
	free(g_pwd);
	g_pwd = e_strdup(path);
	return (1);
}
