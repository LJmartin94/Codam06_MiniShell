/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 09:38:22 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/29 13:48:58 by jsaariko      ########   odam.nl         */
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
*/

int	ft_unset(t_vector *env, t_icomp *cmd)
{
	int index;

	if (cmd->arg == NULL)
		return (0);
	index = vector_search(env, compare_key, (void *)cmd->arg);
	if (index == -1)
		return (0);
	t_env *thingy = vector_get(env, index);
	free_env_item(thingy);
	vector_delete(env, index);
	return (0);
}
