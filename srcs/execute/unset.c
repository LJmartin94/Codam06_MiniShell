/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 09:38:22 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/09 14:12:44 by jsaariko      ########   odam.nl         */
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

static void	unset_item(t_vector *env, t_arg *arg)
{
	int		index;
	t_env	*cur;

	index = vector_search(env, compare_key, (void *)arg->value);
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
		if (validate_env_key(arg->value) == 1 && arg->value[0] != '\0')
		{
			error_str = ft_strjoin(arg->value, ": Not a valid identifier");
			cmd_error(cmd, error_str);
			free(error_str);
			ret = 1;
		}
		else
			unset_item(env, arg);
		arg = arg->right;
	}
	(void)fd;
	return (ret);
}
