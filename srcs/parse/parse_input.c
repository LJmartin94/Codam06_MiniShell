/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 12:04:04 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/14 16:13:13 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "error.h"

void	parse_input(const char *input, t_icomp *comp_blocks)
{
	t_token *tokens;

	tokens = get_tokens(input);
	ft_compconst(comp_blocks);
	manage_fsm(tokens, comp_blocks);
	free_tokens(tokens);
}
