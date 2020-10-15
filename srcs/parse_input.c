/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 12:04:04 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/15 12:09:36 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"//
// #include "fsm.h"//
#include "parse.h"

void	parse_input(const char *input)
{
	t_token *tokens;
	tokens = get_tokens(input);
	// manage_fsm(input);
	ft_printf("%s\n", input);
}
