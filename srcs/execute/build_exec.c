/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 10:38:24 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/28 16:06:58 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include <sys/types.h>
#include <sys/stat.h>

//TODO: Make sure how it works for multiple params
char		**build_argv(t_icomp *comp)
{
	int		i;
	int		j;
	char	**argv;

	i = 0;
	j = 0;
	t_arg *arg = comp->arg;
	while(arg)
	{
		i++;
		arg = arg->right;
	}
	argv = (char **)e_malloc(sizeof(char *) * (i + 2));
	argv[j] = comp->cmd;
	j++;
	i = 0;
	arg = comp->arg;
	while (arg)
	{
		ft_dprintf(STDOUT_FILENO, "%p\n", arg);
		if (arg->value[0] == '\0')
			argv[j] = NULL; //TODO: I doubt this will lead to a memleak?
		else
			argv[j] = arg->value;
		i++;
		j++;
		arg = arg->right;
	}
	argv[j] = NULL;
	j = 0;
	while (argv[j] != NULL)
	{
		ft_dprintf(STDOUT_FILENO, "[%s]\n", argv[j]);
		j++;
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
