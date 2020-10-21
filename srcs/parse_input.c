/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 12:04:04 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/21 18:57:12 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"

/*
** TO DO token linked list and the malloc'd strings inside it still need to
** to be freed after manage_fsm is called.
*/

void	parse_input(const char *input)
{
	t_token *tokens;

	tokens = get_tokens(input);
	manage_fsm(tokens);
}
