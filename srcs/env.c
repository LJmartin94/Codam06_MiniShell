/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 11:49:12 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/24 13:11:15 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "execute.h"
#include "parse.h" //

static int				validate_env(char *env_str)
{
	int i;

	i = 0;
	if (env_str[i] == '=')
		return (-1);
	while (env_str[i] != '\0')
	{
		if (env_str[i] == '=')
			break ;
		i++;
	}
	if (env_str[i + 1] == '\0')
		return(0);
	return (1);
}

/*
** //TODO: if strlcpy fails?
*/

t_env			*get_env_item(char *env_str)
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
	if (ft_strncmp(item->key, "SHLVL", 5) == 0)
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

t_vector		*convert_env(char **envp)
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

static void		write_key_val_pair(char *key, char *value)
{
	write(STDIN_FILENO, key, ft_strlen(key));
	write(STDIN_FILENO, "=", 1);
	write(STDIN_FILENO, value, ft_strlen(value));
	write(STDIN_FILENO, "\n", 1);
}

/*
** //TODO: how can env fail and what is the return value:
** returns >0 if error occurs, 126 if env is not able to be used 127
** if env was not found
*/

int				ft_env(t_vector *env)
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
	return (0);
}

int compare(t_env *data, char *item)
{
	return (ft_strncmp(item, data->key, ft_strlen(data->key)));
}

int				vector_search(t_vector *v, int (*cmp)(), void *item)
{
	size_t i = 0;
	while (i < v->amt)
	{
		// ft_dprintf(STDIN_FILENO, "%s\n", *(char **)(v->data[i]));
		if (cmp(v->data[i], item) == 0)
			return (i);
		i++;
	}
	return (-1);
}

// int				vector_delete_free(t_vector *v, size_t index)
// {
// 	size_t i;
// 	if (index <= 0 || index > v->amt)
// 		return (0);
// 	// v->data[index];
// 	// free(v->data[index]);
// 	v->data[index] = NULL;
// 	i = index;
// 	while (i < v->amt)
// 	{
// 		v->data[i] = v->data[i + 1];
// 		i++;
// 	}
// 	if (!vector_resize(v, v->amt - 1))
// 		error_exit_errno();
// 	return (1);
// }

int				ft_unset(t_vector *env, char *cmd)
{
	int index = vector_search(env, compare, (void *)cmd);
	ft_dprintf(STDIN_FILENO, "%d\n", index);
	// vector_delete_free(env, (size_t)index);
	return (0);
}

int				ft_export(t_vector *env, char *cmd)
{
	t_env *item;
	int ret;

	ret = validate_env(cmd);
	if (ret == -1)
	{
		ft_dprintf(STDERR_FILENO, "Export: '%s': not a valid identifier", cmd); //turn into actual error msg that quits the thing
		return (0);
	}
	item = get_env_item(cmd);
	if (item == NULL)
		return (0);
	ret = vector_push(env, item);
	if (!ret)
		error_exit_errno();
	return (0);
}
