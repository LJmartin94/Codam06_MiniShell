/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_string.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 17:48:44 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/12 17:49:53 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_STRING_H
# define T_STRING_H

# include "libft.h"

typedef struct	s_string
{
	char	*string;
	size_t	len;
}				t_string;

int string_splice(t_string *string, int start, int del, char *value);

#endif