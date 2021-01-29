/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_basic_and_escape_states.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 18:07:18 by lindsay       #+#    #+#                 */
/*   Updated: 2021/01/29 11:57:45 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_transition_code	sh_rd_basic_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_redir				*last;

	last = (*icur)->rdhead;
	while (last->right != NULL)
		last = last->right;
	ft_add_token_to_comp((*this), &(last->file));
	*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_rd_bs_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_redir				*last;

	last = (*icur)->rdhead;
	while (last->right != NULL)
		last = last->right;
	if (recognise_token_state(*this) == backslash && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	if (id == exit_state)
		return (error);
	if ((*this) != NULL)
	{
		ft_add_token_to_comp((*this), &(last->file));
		*this = (*this)->next;
	}
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}
