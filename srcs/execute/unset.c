/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 09:38:22 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/11 15:28:51 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	compare_key(t_env *data, char *item)
{
	return (ft_strncmp(item, data->key, ft_strlen(data->key)));
}

/*
** //TODO: Man says this unset should return a non zero value if arg doesn't
** exist, but I can't make it happen
** The exit status is true unless a name is readonly.
** // can unset multiple variables at once
** 
*/

int	ft_unset(t_vector *env, t_icomp *cmd, int fd)
{
	int		index;
	t_env	*cur;

	(void)fd;
	if (ft_strncmp(cmd->arg, "", 1) == 0)
		return (0);
	index = vector_search(env, compare_key, (void *)cmd->arg);
	if (index == -1)
		return (0);
	cur = vector_get(env, index);
	free_env_item(cur);
	vector_delete(env, index);
	return (0);
}
