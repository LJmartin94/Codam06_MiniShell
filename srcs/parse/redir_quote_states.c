/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_quote_states.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 18:07:18 by lindsay       #+#    #+#                 */
/*   Updated: 2020/12/04 16:29:31 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_transition_code	sh_rd_dq_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_redir				*last;

	last = (*icur)->rdhead;
	while (last->right != NULL)
		last = last->right;
	if (recognise_token_state(*this) == dq && *this)
		*this = (*this)->next;
	if (recognise_token_state(*this) != backslash && \
	recognise_token_state(*this) != dq && *this)
	{
		ft_add_token_to_comp((*this), &(last->file));
		*this = (*this)->next;
	}
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_rd_exit_quote_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	(void)icur;
	if ((recognise_token_state(*this) == dq || \
	recognise_token_state(*this) == sq) && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_rd_dq_bs_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_redir				*last;

	last = (*icur)->rdhead;
	while (last->right != NULL)
		last = last->right;
	if (recognise_token_state(*this) == backslash && *this)
		*this = (*this)->next;
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

t_transition_code	sh_rd_sq_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_redir				*last;

	last = (*icur)->rdhead;
	while (last->right != NULL)
		last = last->right;
	if (recognise_token_state(*this) == sq && *this)
		*this = (*this)->next;
	if (recognise_token_state(*this) != sq && *this)
	{
		ft_add_token_to_comp((*this), &(last->file));
		*this = (*this)->next;
	}
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}
