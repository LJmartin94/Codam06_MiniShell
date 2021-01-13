/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_internal.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 13:50:48 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/13 13:56:19 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execute.h"
#include "error.h"

void update_pwd(t_vector *env)
{
	t_env *env_path;
	char *cwd;

	cwd = NULL;
	env_path = vector_get(env, vector_search(env, compare_key, (void *)"PWD"));
	free(env_path->value);
	cwd = getcwd(cwd, 0);
	env_path->value = ft_strdup(cwd);
	free(g_pwd);
	g_pwd = ft_strdup(cwd);
	free(cwd);
}

void		cd_error(char *path)
{
	e_write(STDERR_FILENO, "Could not access ", 17);
	e_write(STDERR_FILENO, path, ft_strlen(path));
	e_write(STDERR_FILENO, "\n", 1);
}

int			escape_being_lost(t_vector *env, char *path)
{
	char **split;
	int i;
	int len;
	int dir;

	i = 0;
	split = ft_split(path, '/');
	while (split[i] != NULL)
	{
		if (split[i + 1] == NULL && ft_strncmp(split[i], "..", 3) == 0 )
		{
			len = ft_strlen(split[i - 1]) + 4;
			ft_bzero(path + ft_strlen(path) - len, len);
			dir = chdir(path);
			free_matrix(split);
			if (dir == -1)
				break ;
			else
			{
				update_pwd(env);
				free(path);
				return(0);				
			}
		}
		i++;
	}
	cd_error(path);
	free(g_pwd);
	g_pwd = ft_strdup(path);
	free(path);
	return(1);
}
