/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 12:51:50 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/13 13:08:08 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

/*
** //TODO: Make work with multiple args
*/

static t_env	*expand_find(t_vector *env, char *pos)
{
	int		len;
	char	*key;
	int		index;
	t_env	*item;

	len = ft_strchrset(pos, " ");
	if (len > 0)
	{
		key = (char *)e_malloc(sizeof(char) * len + 1);
		key = ft_memcpy(key, pos, sizeof(char) * len);
	}
	else
		key = ft_strdup(pos);
	index = vector_search(env, compare_key, key);
	item = vector_get(env, index);
	if (item == NULL)
	{
		item = (t_env *)e_malloc(sizeof(t_env));
		item->key = key;
		item->value = ft_strdup("");
	}
	return (item);
}

static void		replace_arg(t_vector *env, t_icomp *comp, size_t *i)
{
	char	*final;
	t_env	*replace;

	final = NULL;
	if (comp->arg[*i + 1] == '?')
	{
		final = ft_strsplice(comp->arg, *i, 2, ft_itoa(g_ret_val));
		free(comp->arg);
		comp->arg = final;
		i += 2;
	}
	else
	{
		replace = expand_find(env, comp->arg + *i + 1);
		final = ft_strsplice(comp->arg, *i,
					ft_strlen(replace->key) + 1,
					replace->value);
		free(comp->arg);
		comp->arg = final;
		*i = *i - (ft_strlen(replace->key) + 1) + ft_strlen(replace->value);
	}
}

void			expand_env(t_vector *env, t_icomp *comp)
{
	size_t	i;

	i = 0;
	while (comp->arg[i] != '\0')
	{
		if (comp->arg[i] == '$')
			replace_arg(env, comp, &i);
		else
			i++;
	}
}
