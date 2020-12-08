/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 11:19:34 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/08 12:30:51 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

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

t_vector	*envp_to_env(char **envp)
{
	size_t		i;
	t_env		*cur;
	t_vector	*env;
	int			ret;

	i = 0;
	cur = NULL;
	env = (t_vector *)e_malloc(sizeof(t_vector));
	vector_init(env);
	while (envp[i] != NULL)
	{
		cur = get_env_item(envp[i]);
		ret = vector_push(env, cur);
		if (ret == 0)
			error_exit_errno();
		i++;
	}
	return (env);
}

static char	*create_envp_str(t_env *cur)
{
	char	*final;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(cur->key);
	if (tmp == NULL)
		error_exit_errno();
	tmp2 = ft_strjoin(tmp, "=");
	if (tmp2 == NULL)
		error_exit_errno();
	final = ft_strjoin(tmp2, cur->value);
	if (final == NULL)
		error_exit_errno();
	free(tmp);
	tmp = NULL;
	free(tmp2);
	tmp = NULL;
	return (final);
}

char		**env_to_envp(t_vector *env)
{
	char	**envp;
	t_env	*cur;
	size_t	i;

	i = 0;
	envp = (char **)e_malloc(sizeof(char *) * (env->amt + 1));
	while (i < env->amt)
	{
		cur = (t_env *)vector_get(env, i);
		envp[i] = create_envp_str(cur);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int			validate_env_key(const char *arg)
{
	size_t i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
