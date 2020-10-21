/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fsm.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 13:55:59 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/21 15:06:48 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "statetable.h"

void	manage_fsm(t_token *tokens)
{
	t_transition_code	id;
	t_icomp				ihead;
	t_icomp				*icur;
	t_transition_code	(*current_state)(t_token **, t_icomp **);
	int					i;

	ft_compconst(&ihead);
	icur = &ihead;
	current_state = &sh_entry_state;
	while (tokens)
	{
		id = current_state(&tokens, &icur);
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
	current_state(&tokens, &icur);
}
