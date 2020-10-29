/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env_item.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:59:48 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/29 11:30:10 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include "libft.h"

t_env		*get_env_item(char *env_str)
{
	t_env	*item;
	int		i;

	item = (t_env *)e_malloc(sizeof(t_env));
	i = 0;
	while (env_str[i] != '\0' && env_str[i] != '=')
		i++;
	item->key = (char *)e_malloc(sizeof(char) * (i + 1));
	ft_strlcpy(item->key, env_str, i + 1);
	if (env_str[i] != '=')
		item->value = NULL;
	else
	{
		item->value = ft_strdup(env_str + i + 1);
		if (item->value == NULL)
			error_exit_errno();
	}
	return (item);
}
