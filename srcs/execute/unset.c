/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 09:38:22 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/28 17:44:33 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int compare(t_env *data, char *item)
{
	return (ft_strncmp(item, data->key, ft_strlen(data->key)));
}

int	ft_unset(t_vector *env, t_icomp *cmd)
{
	int index;

	if (cmd->arg == NULL)
		return (0); //TODO: return on fail?
	index = vector_search(env, compare, (void *)cmd->arg);
	if (index == -1)
		return (0); //fail
	free(env->data[index]);
	vector_delete(env, (size_t)index);
	return (0);
}