/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 10:38:24 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/26 12:53:47 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include <sys/types.h>
#include <sys/stat.h>

char		**build_argv(t_icomp *comp)
{
	int		i;
	int		j;
	char	**try;
	char	**argv;

	i = 0;
	j = 0;
	try = ft_split(comp->arg, ' ');
	while (try[i] != NULL)
		i++;
	argv = (char **)e_malloc(sizeof(char *) * (i + 2));
	argv[j] = comp->cmd;
	j++;
	i = 0;
	while (try[i] != NULL)
	{
		argv[j] = try[i];
		i++;
		j++;
	}
	argv[j] = NULL;
	free(try);
	try = NULL;
	return (argv);
}

static char	*check_path(char *path, char *cmd, struct stat stat_struct)
{
	char *tmp;
	char *final;

	tmp = ft_strjoin(path, "/");
	final = ft_strjoin(tmp, cmd);
	free(tmp);
	if (stat(final, &stat_struct) == 0)
		return (final);
	free(final);
	return (NULL);
}

char		*find_path(t_vector *env, t_icomp *comp)
{
	t_env		*path;
	char		**paths;
	size_t		i;
	struct stat	stat_struct;
	char		*final;

	if (stat(comp->cmd, &stat_struct) == 0)
		return (ft_strdup(comp->cmd));
	path = vector_get(env, vector_search(env, compare_key, "PATH"));
	paths = ft_split(path->value, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		final = check_path(paths[i], comp->cmd, stat_struct);
		if (final != NULL)
		{
			free_matrix(paths);
			paths = NULL;
			return (final);
		}
		i++;
	}
	free_matrix(paths);
	paths = NULL;
	return (NULL);
}
