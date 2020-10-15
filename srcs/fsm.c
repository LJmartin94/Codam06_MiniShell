/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fsm.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 13:55:59 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/15 20:26:50 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"
#include "fsm.h"
#include "statetable.h"

int		ft_compconst(t_icomp *tonull)
{
	tonull->sep = NULL;
	tonull->cmd = NULL;
	tonull->opt = NULL;
	tonull->arg = NULL;
	tonull->next = NULL;
	return (0);
}

void	manage_fsm(t_token *tokens)
{
	t_token 			*this;
	t_transition_code	id;
	t_icomp				ihead;
	t_icomp				*icur;
	t_transition_code	(*current_state)(t_token *, t_icomp *);
	int					i;

	this = tokens;
	ft_compconst(&ihead);
	icur = &ihead;
	current_state = &sh_entry_state;
	while (this->next)
	{
		id = current_state(this, icur);
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
		this = this->next;
	}
}