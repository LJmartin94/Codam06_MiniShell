/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 11:51:51 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/22 15:19:17 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# define VECTOR_INIT_CAPACITY 4

typedef struct	s_vector
{
	void	**data;
	size_t	item_size;
	size_t	amt;
}				t_vector;

int vector_init(t_vector *v);
int vector_total(t_vector *v);
int vector_add(t_vector *v, void *item);
int vector_set(t_vector *v, int index, void *item);
void *vector_get(t_vector *v, size_t index);
int vector_delete(t_vector *v, int index);
int vector_free(t_vector *v);

#endif