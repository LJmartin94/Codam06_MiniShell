/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 09:38:22 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/28 16:28:52 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	compare_key(t_env *data, char *item)
{
	// ft_dprintf(STDOUT_FILENO, "compare_key data: [%s], item: [%s]\n", data->key, item);
	int ret = ft_strncmp(item, data->key, ft_strlen(data->key) + 1);
	// ft_dprintf(STDOUT_FILENO, "end compare\n");
	return (ret);//TODO: make sure this doesn't segfault
}

/*
** //TODO: Man says this unset should return a non zero value if arg doesn't
** exist, but I can't make it happen
** The exit status is true unless a name is readonly.
** // can unset multiple variables at once
*/

int	ft_unset(t_vector *env, t_icomp *cmd, int fd)
{
	int		index;
	t_env	*cur;
	t_arg	*arg;
	int		ret;

	(void)fd;
	arg = cmd->arg;
	ret = 0;
	while(arg)
	{
		if (ft_strncmp(cmd->arg->value, "", 1) == 0)
		{
			ret = 1;
			break ;
		}
		index = vector_search(env, compare_key, (void *)cmd->arg);
		if (index == -1)
			break ;
		cur = vector_get(env, index);
		free_env_item(cur);
		vector_delete(env, index);
		arg = arg->right;
	}
	return (ret);
}
