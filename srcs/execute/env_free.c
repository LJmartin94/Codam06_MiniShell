/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_free.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:59:48 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/29 14:01:27 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include "libft.h"

void			free_env_item(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void			free_environment(t_vector *env)
{
	size_t	i;
	t_env	*cur;

	i = 0;
	while (i < env->amt)
	{
		cur = vector_get(env, i);
		free_env_item(cur);
		i++;
	}
	free(env->data);
	free(env);
}

void			free_envp(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
