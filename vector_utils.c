/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:22:25 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/22 18:05:34 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

int			vector_init(t_vector *v)
{
	if (v == NULL)
		return (0);
	v->item_size = 0;
	v->amt = 0;
	v->data = NULL;
	return (1);
}

static int	vector_resize(t_vector *v, size_t new_amt)
{
	void **data;

	data = ft_realloc(v->data, new_amt * v->item_size);
	if (!data)
		return (0);
	v->data = data;
	return (1);
}

int			vector_push(t_vector *v, void *item)
{
	if (v->item_size < 1)
	{
		size_t size = sizeof(item);
		v->item_size = size;
	}
	if (v == NULL || sizeof(item) != v->item_size)
		return (0);
	vector_resize(v, v->amt + 1);
	v->data[v->amt] = item;
	v->amt++;
	return (1);
}

void 		*vector_get(t_vector *v, size_t index)
{
    if (index >= 0 && index < v->amt)
	{
		ft_dprintf(STDIN_FILENO, "%p\n", v->data[index]);
		ft_dprintf(STDIN_FILENO, "%p\n", v->data[index]);
        return (v->data[index]);
	}
	return (NULL);
}