/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dq_bs_basic_states.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/08 16:22:46 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/08 17:04:45 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_transition_code	sh_dq_bs_cmd_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	if (recognise_token_state(*this) == backslash && *this)
		*this = (*this)->next;
	if ((*this) != NULL)
	{
		ft_add_token_to_comp((*this), &((*icur)->cmd));
		*this = (*this)->next;
	}
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_dq_bs_opt_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	if (recognise_token_state(*this) == backslash && *this)
		*this = (*this)->next;
	if ((*this) != NULL)
	{
		ft_add_token_to_comp((*this), &((*icur)->arg));
		*this = (*this)->next;
	}
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_dq_bs_arg_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	if (recognise_token_state(*this) == backslash && *this)
		*this = (*this)->next;
	if ((*this) != NULL)
	{
		ft_add_token_to_comp((*this), &((*icur)->arg));
		*this = (*this)->next;
	}
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}