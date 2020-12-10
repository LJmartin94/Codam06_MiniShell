/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 10:38:24 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/08 16:03:51 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include <sys/types.h>
#include <sys/stat.h>

/*
** //TODO: line 45: I doubt this will lead to a memleak?
*/

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
	if (path == NULL)
		return (NULL);
	paths = ft_split(path->value, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		final = check_path(paths[i], comp->cmd, stat_struct);
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
