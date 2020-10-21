/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fsm.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 13:55:59 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/21 13:25:10 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "statetable.h"
#include <stdio.h> //remove

void	manage_fsm(t_token *tokens)
{
	t_token 			*this;
	t_transition_code	id;
	t_icomp				ihead;
	t_icomp				*icur;
	t_transition_code	(*current_state)(t_token **, t_icomp **);
	int					i;

	this = tokens;
	ft_compconst(&ihead);
	icur = &ihead;
	current_state = &sh_entry_state;
	printf("Head at start of loop: [%p]\n Curr at start of loop: [%p]\n", &ihead, icur);
	while (this)
	{
		id = current_state(&this, &icur);
		i = 0;
		while (&g_shellstate_table[i])
		{
			if ((&g_shellstate_table[i])->orig_state == current_state && \
			(&g_shellstate_table[i])->transition_code == id)
			{
				current_state = (&g_shellstate_table[i])->next_state;
				break ;
			}
			i++;
		}
	}
	current_state(&this, &icur);
	printf("Head at end of loop: [%p]\n Curr at end of loop: [%p]\n", &ihead, icur);
	icur = &ihead;
	while (icur)
	{
		printf("Block:	|%d|\nADR:	|%p|\nCMD:	|%s|\nOPT:	|%s|\nARG:	|%s|\nSEP:	|%s|\nRGT: [%p]\nLFT: [%p]\n", icur->id, icur, icur->cmd, icur->opt, icur->arg, icur->sep, icur->right, icur->left);
		icur = icur->right;
	}
}
