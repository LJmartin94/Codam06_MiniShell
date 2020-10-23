/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 11:49:12 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/24 13:07:42 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "execute.h"

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

void write_key_val_pair(char *key, char *value)
{
	write(STDIN_FILENO, key, ft_strlen(key));
	write(STDIN_FILENO, "=", 1);
	write(STDIN_FILENO, value, ft_strlen(value));
	write(STDIN_FILENO, "\n", 1);
}

int		ft_env(t_vector *env)
{
	size_t	i;
	t_env	*cur;

	i = 0;
	cur = NULL;
	while (i < env->amt)
	{
		cur = (t_env *)vector_get(env, i);
		write_key_val_pair(cur->key, cur->value);
		i++;
	}
	return (0);//TODO: how can env fail and what is the return value:
	// returns >0 if error occurs, 126 if env is not able to be used 127 if env was not found
}

t_vector	*convert_env(char **envp)
{
	size_t		i;
	size_t		count;
	t_env	*cur;
	int ret;
	t_vector *env;

	i = 0;
	count = 0;
	cur = NULL;
	while(envp[count])
		count++;
	env = (t_vector *)e_malloc(sizeof(t_vector));
	vector_init(env);
	ft_dprintf(STDIN_FILENO, "%d, %d, %p\n", env->amt, env->item_size, env->data);
	if (env->item_size == 0)
		ft_dprintf(STDIN_FILENO, "zeroooo\n\n");
	while(i < count)
	{
		ft_dprintf(STDIN_FILENO, "%s\n", envp[i]);
		cur = get_env_item(envp[i]);
		ret = vector_push(env, cur);
		if (!ret)
			error_exit_errno();
		i++;
	}
	return (NULL);
}