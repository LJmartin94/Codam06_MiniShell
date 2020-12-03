/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 09:38:22 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/03 15:34:23 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
** //TODO: make sure this doesn't segfault
** //TODO: Move to other file
*/

int			compare_key(t_env *data, char *item)
{
	int ret;

	ret = ft_strncmp(item, data->key, ft_strlen(data->key) + 1);
	return (ret);
}

/*
** //TODO: Man says this unset should return a non zero value if arg doesn't
** exist, but I can't make it happen
** The exit status is true unless a name is readonly.
** // can unset multiple variables at once
*/

static void	unset_item(t_vector *env, t_icomp *cmd, int fd)
{
	int		index;
	t_env	*cur;

	index = vector_search(env, compare_key, (void *)cmd->arg);
	if (index != -1)
	{
		cur = vector_get(env, index);
		free_env_item(cur);
		vector_delete(env, index);
	}
}

int			ft_unset(t_vector *env, t_icomp *cmd, int fd)
{
	t_arg	*arg;
	int		ret;
	char	*error_str;

	arg = cmd->arg;
	ret = 0;
	while (arg)
	{
		if (validate_env_key(arg->value) == 1)
		{
			error_str = ft_strjoin(arg->value, ": Not a valid identifier");
			cmd_error(cmd, error_str, fd);
			free(error_str);
			ret = 1;
		}
		else
			unset_item(env, cmd, fd);
		arg = arg->right;
	}
	return (ret);
}
