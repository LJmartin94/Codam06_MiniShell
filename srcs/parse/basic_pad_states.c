/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   basic_pad_states.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 13:30:27 by lindsay       #+#    #+#                 */
/*   Updated: 2020/11/06 14:01:03 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_transition_code	sh_cmd_pad_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	while (recognise_token_state(*this) == padding && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_opt_pad_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	int					valid;

	valid = validate_option_flags(icur);
	while (recognise_token_state(*this) == padding && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	if (id == option && valid == 0)
		id = arg;
	return (id);
}

t_transition_code	sh_arg_pad_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	while (recognise_token_state(*this) == padding && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}
