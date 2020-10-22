/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 11:49:12 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/22 16:32:20 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "error.h"
#include "vector.h"

t_env	*get_env_item(char *env_str)
{
	int	i;
	t_env	*item;

	(void)env_str;
	item = (t_env *)e_malloc(sizeof(t_env));
	i = 0;
	while (env_str[i] != '=')
		i++;
	item->key = (char *)e_malloc(sizeof(char) * (i + 1));
	int ret = ft_strlcpy(item->key, env_str, i + 1);
	if (ret == -1) //TODO: if strlcpy fails?
		ft_dprintf(STDERR_FILENO, "rip ft_strlcpy in get_env_item");
	item->value = ft_strdup(env_str + i + 1);
	if (item->value == NULL)
		error_exit_errno();
	return (item);
}

t_vector	*convert_env(char **envp)
{
	size_t		i;
	size_t		count;
	t_env		*cur;
	t_vector 	*env;
	int 		ret;

	i = 0;
	count = 0;
	cur = NULL;
	while (envp[count])
		count++;
	env = (t_vector *)e_malloc(sizeof(t_vector));
	vector_init(env);
	while (i < count)
	{
		cur = get_env_item(envp[i]);
		ret = vector_push(env, cur);
		if (!ret)
			error_exit_errno();
		free(cur);
		i++;
	}
	return (env);
}
