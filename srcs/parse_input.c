/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 12:04:04 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/26 12:02:17 by jsaariko      ########   odam.nl         */
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
	// print_tokens(tokens);
	free_tokens(tokens);
}

/*
** //TODO: Remove print_tokens function when no longer debugging.
*/

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		e_write(1, "|", 1);
		e_write(1, tokens->token, ft_strlen(tokens->token));
		e_write(1, "| ", 2);
		tokens = tokens->next;
	}
	e_write(1, "\n", 1);
}
