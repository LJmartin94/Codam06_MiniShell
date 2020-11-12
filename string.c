/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 17:31:03 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/12 18:04:25 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "t_string.h"

int string_splice(t_string *string, int start, int del, char *value)
{
	char *new;
	size_t len_new;

	size_t value_len = ft_strlen(value);
	len_new = string->len - del + value_len + 1;
	new = (char *)calloc(len_new, sizeof(char));
	if (!new)
		return (0);
	ft_memcpy(new, string->string, start);
	ft_memcpy(new + start, value, value_len);
	ft_memcpy(new + start + value_len,
			string->string + start + del,
			string->len - start - del);
	free(string->string);
	string->string = new;
	string->len = len_new;
	return (1);
}