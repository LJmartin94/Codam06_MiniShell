/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dq_exit_basic_states.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 18:10:03 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/06 14:41:58 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "error.h"

t_transition_code	sh_dq_exit_cmd_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	(void)icur;
	if (recognise_token_state(*this) == dq && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_dq_exit_opt_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	(void)icur;
	if (recognise_token_state(*this) == dq && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_dq_exit_arg_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	(void)icur;
	if (recognise_token_state(*this) == dq && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}
