/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 11:49:12 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/22 15:36:10 by jsaariko      ########   odam.nl         */
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

int		vector_init(t_vector *v)
{
	if (v == NULL)
		return (0);
	v->item_size = 0;
	v->amt = 0;
	v->data = NULL;
	return (1);
}

int		vector_resize(t_vector *v, size_t new_amt)
{
	void **data;

	data = ft_realloc(v->data, new_amt * v->item_size);
	if (data)
	{
		v->data = data;
		return (1);
	}
	return (0);
}

int		vector_push(t_vector *v, void *item)
{
	// ft_dprintf(STDIN_FILENO, "lol %p, %d\n", v, sizeof(item));
	// ft_dprintf(STDIN_FILENO, "%d\n", v->item_size);
	if (v->item_size < 1)
	{
		// ft_dprintf(STDIN_FILENO, "here?????\n");
		size_t size = sizeof(item);
		// ft_dprintf(STDIN_FILENO, "size is: %d\n", size);
		v->item_size = size;
		// ft_dprintf(STDIN_FILENO, "passed to item_size: %d\n", v->item_size);
	}
	if (v == NULL || sizeof(item) != v->item_size)
	{
		// ft_dprintf(STDIN_FILENO, "or mabbe here?????\n");		
		return (0);
	}
	// ft_dprintf(STDIN_FILENO, "here?\n");
	vector_resize(v, v->amt + 1);
	// ft_dprintf(STDIN_FILENO, "v->amt + 1 = %d\n", v->amt + 1);
	v->data[v->amt] = item;
	// ft_dprintf(STDIN_FILENO, "This one dies?\n");
	v->amt++;
	return (1);
}
// void vector_init(vector *v)
// {
    // v->capacity = VECTOR_INIT_CAPACITY;
    // v->total = 0;
    // v->items = malloc(sizeof(void *) * v->capacity);
// }

void 	*vector_get(t_vector *v, size_t index)
{
    if (index >= 0 && index < v->amt)
        return v->data[index];
    return NULL;
}

t_env	*convert_env(char **envp)
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
		// ft_dprintf(STDIN_FILENO, "RET: %d\n\n", ret);
		t_env *item = (t_env *)vector_get(env, i);
		ft_dprintf(STDIN_FILENO, "%s=%s\n", item->key, item->value);
		free(cur);
		i++;
	}
	return (NULL);
}