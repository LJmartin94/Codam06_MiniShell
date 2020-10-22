/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 12:04:04 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/22 22:36:47 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "error.h"


/*
** TO DO token linked list and the malloc'd strings inside it still need to
** to be freed after manage_fsm is called.
*/

#include <stdio.h>
void	print_tokens(t_token *tokens);
void	print_components(t_icomp *icur);

void	parse_input(const char *input)
{
	t_token *tokens;
	t_icomp	*component_blocks;

	tokens = get_tokens(input);
	component_blocks = manage_fsm(tokens);
	print_tokens(tokens);
	print_components(component_blocks);
	free_tokens(tokens);
	free_components(component_blocks);
}

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

void	print_components(t_icomp *icur)
{
	while (icur)
	{
		printf("Block:	|%d|\nADR:	|%p|\nCMD:	|%s|\nOPT:	|%s|\nARG:	|%s|\nSEP:	|%s|\nRGT: [%p]\nLFT: [%p]\n", icur->id, icur, icur->cmd, icur->opt, icur->arg, icur->sep, icur->right, icur->left);
		icur = icur->right;
	}
}

//a & a & a & a & a & a & a & a & a & a & a & a & a & a & a & a & a & a