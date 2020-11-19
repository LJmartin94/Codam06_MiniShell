/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dq_exit_basic_states.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 18:10:03 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/19 15:32:43 by limartin      ########   odam.nl         */
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
	int 				valid;

	if (recognise_token_state(*this) == dq && *this)
		*this = (*this)->next;
	valid = validate_option_flags(icur);
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	if (valid == -1)
		id = demote_option_state(id);
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
