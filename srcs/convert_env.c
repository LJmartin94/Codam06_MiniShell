/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 11:19:34 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/28 18:28:56 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

t_env	*get_env_item(char *env_str)
{
	t_env	*item;
	int		i;
	int		shlvl;
	int		ret;

	item = (t_env *)e_malloc(sizeof(t_env));
	i = 0;
	while(env_str[i] != '=')
		i++;
	item->key = (char *)e_malloc(sizeof(char) * (i + 1));
	ret = ft_strlcpy(item->key, env_str, i + 1); //TODO: or if there's nothing behind =   ??
	if (ret == -1)
		ft_dprintf(STDERR_FILENO, "rip ft_strlcpy in get_env_item");
	if (ft_strncmp(item->key, "SHLVL", 6) == 0) //TODO: ???
	{
		shlvl = ft_atoi(env_str + i + 1);
		shlvl++;
		item->value = ft_itoa(shlvl);
	}
	else
		item->value = ft_strdup(env_str + i + 1);
	if (item->value == NULL)
		error_exit_errno();
	return (item);
}

t_vector		*envp_to_env(char **envp)
{
	size_t		i;
	size_t		count;
	t_env		*cur;
	t_vector	*env;
	int			ret;

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
		if (cur == NULL)
		{
			ft_dprintf(STDERR_FILENO, "ENV ITEM RETURNS NULL WHERE IT SHOULDN'T\n");
			return (NULL);
		}
		ret = vector_push(env, cur);
		if (!ret)
			error_exit_errno();
		i++;
	}
	return (env);
}

int		free_env(t_vector *env)
{
	size_t i;
	t_env *cur;

	i = 0;
	while (i < env->amt)
	{
		cur = vector_get(env, i);
		free(cur->key);
		free(cur->value);
		free(cur);
		i++;
	}
	free(env->data);
	free(env);
	return (0);
}

int		free_envp(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	return (0);
}


char **env_to_envp(t_vector *env)
{
	char **envp;
	char *tmp;
	char *tmp2;
	t_env *cur;
	size_t i;

	i = 0;
	envp = (char **)e_malloc(sizeof(char *) * (env->amt + 1));
	while (i < env->amt)
	{
		cur = (t_env *)vector_get(env, i);
		tmp = ft_strdup(cur->key);
		if (tmp == NULL)
			error_exit_errno();
		tmp2 = ft_strjoin(tmp, "=");
		if (tmp2 == NULL)
			error_exit_errno();
		envp[i] = ft_strjoin(tmp2, cur->value);
		if (envp[i] == NULL)
			error_exit_errno();
		free(tmp);
		tmp = NULL;
		free(tmp2);
		tmp = NULL;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}