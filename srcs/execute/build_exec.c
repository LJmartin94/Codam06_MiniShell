/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 10:38:24 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/29 12:36:09 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include <sys/types.h>
#include <sys/stat.h>

char		**build_argv(t_icomp *comp)
{
	int		i;
	char	**argv;
	t_arg	*arg;

	i = 0;
	arg = comp->arg;
	while (arg)
	{
		i++;
		arg = arg->right;
	}
	argv = (char **)e_malloc(sizeof(char *) * (i + 2));
	argv[0] = comp->cmd;
	i = 1;
	arg = comp->arg;
	while (arg)
	{
		if (arg->value[0] == '\0')
			argv[i] = NULL;
		else
			argv[i] = arg->value;
		i++;
		arg = arg->right;
	}
	return (argv);
}

static char	*check_path(char *path, char *cmd)
{
	char *tmp;
	char *final;
	struct stat	stat_struct;

	tmp = ft_strjoin(path, "/");
	final = ft_strjoin(tmp, cmd);
	free(tmp);
	if (stat(final, &stat_struct) == 0)
		return (final);
	free(final);
	return (NULL);
}

char		*get_from_path(t_vector *env, t_icomp *comp)
{
	t_env		*path;
	char		**paths;
	size_t		i;
	char		*final;
	
	path = vector_get(env, vector_search(env, compare_key, "PATH"));
	if (path == NULL)
		return (NULL);
	paths = ft_split(path->value, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		final = check_path(paths[i], comp->cmd);
		if (final != NULL)
		{
			free_matrix(paths);
			return (final);
		}
		i++;
	}
	free_matrix(paths);
	return (NULL);
}

char		*find_path(t_vector *env, t_icomp *comp)
{
	struct stat	stat_struct;

	if (ft_strncmp(comp->cmd, "./", 2) == 0)
		return(ft_strdup(comp->cmd));
	if (ft_strncmp(comp->cmd, "/", 1) == 0)
	{
		if (stat(comp->cmd, &stat_struct) == 0)
			return (ft_strdup(comp->cmd));
		else
			return (NULL);
	}
	return (get_from_path(env, comp));
}
