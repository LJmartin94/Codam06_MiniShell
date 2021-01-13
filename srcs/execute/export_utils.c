/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 18:05:57 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/13 19:21:28 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

int		env_no_params(t_vector *env, int fd)
{
	size_t	i;
	t_env	*cur;

	i = 0;
	cur = NULL;
	while (i < env->amt)
	{
		cur = (t_env *)vector_get(env, i);
		e_write(fd, "declare -x ", 11);
		e_write(fd, cur->key, ft_strlen(cur->key));
		if (cur->value != NULL)
		{
			e_write(fd, "=\"", 2);
			e_write(fd, cur->value, ft_strlen(cur->value));
			e_write(fd, "\"", 1);
		}
		e_write(fd, "\n", 1);
		i++;
	}
	return (0);
}

void	edit_env(t_vector *env, t_env *item, int pos)
{
	t_env	*edit;

	if (pos != -1)
	{
		edit = vector_get(env, pos);
		if (item->value != NULL)
		{
			free(edit->value);
			edit->value = item->value;
			free(item->key);
			item->key = NULL;
			free(item);
			item = NULL;
		}
		else
		{
			free_env_item(item);
			item = NULL;
		}
	}
	else
	{
		if (vector_push(env, item) == 0)
			error_exit_errno();
	}
}

char	*export_join_args(t_arg **arg)
{
	char *str;
	char *str2;

	str = ft_strdup((*arg)->value);
	if (!str)
		error_exit_errno();
	while ((*arg)->pad[0] == '\0' && (*arg)->right != NULL)
	{
		str2 = e_strjoin(str, (*arg)->right->value);
		free(str);
		str = ft_strdup(str2);
		if (!str)
			error_exit_errno();
		free(str2);
		(*arg) = (*arg)->right;
	}
	return (str);
}
