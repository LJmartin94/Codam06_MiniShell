/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 11:51:51 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/22 16:23:49 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>//

typedef struct	s_vector
{
	void	**data;
	size_t	item_size;
	size_t	amt;
}				t_vector;

int vector_init(t_vector *v);
int vector_push(t_vector *v, void *item);
void *vector_get(t_vector *v, size_t index);

#endif