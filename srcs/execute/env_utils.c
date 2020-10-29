/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 11:19:34 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/29 10:59:46 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

t_vector	*envp_to_env(char **envp)
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
		ret = vector_push(env, cur);
		if (ret == 0)
			error_exit_errno();
		i++;
	}
	return (env);
}

int			free_env(t_vector *env)
{
	size_t	i;
	t_env	*cur;

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

int			free_envp(char **envp)
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
