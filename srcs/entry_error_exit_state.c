/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   entry_error_exit_state.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 18:10:03 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/21 14:59:11 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_transition_code	sh_entry_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	(void)icur;
	id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_error_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	(void)icur;
	*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_exit_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	(void)icur;
	(void)this;
	id = exit_state;
	return (id);
}
