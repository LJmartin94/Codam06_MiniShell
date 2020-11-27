/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 09:38:22 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/27 16:45:07 by jsaariko      ########   odam.nl         */
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

	(void)fd;
	if (ft_strncmp(cmd->arg->value, "", 1) == 0)
		return (0);
	index = vector_search(env, compare_key, (void *)cmd->arg);
	if (index == -1)
		return (0);
	cur = vector_get(env, index);
	free_env_item(cur);
	vector_delete(env, index);
	return (0);
}
