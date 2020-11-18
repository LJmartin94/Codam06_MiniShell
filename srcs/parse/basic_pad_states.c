/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   basic_pad_states.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 13:30:27 by lindsay       #+#    #+#                 */
/*   Updated: 2020/11/18 16:22:56 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_transition_code			sh_cmd_pad_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	(void)icur;
	while (recognise_token_state(*this) == padding && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

static t_transition_code	demote_option_state(t_transition_code id)
{
	if (id == opt)
		id = arg;
	else if (id == dq)
		id = dqarg;
	else if (id == sq)
		id = sqarg;
	else if (id == backslash)
		id = bsarg;
	return (id);
}

t_transition_code			sh_opt_pad_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	int					valid;
	t_token				*pad;
	t_arg				*last;

	pad = *this;
	valid = validate_option_flags(icur);
	while (recognise_token_state(*this) == padding && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	if (valid == 0)
		id = demote_option_state(id);
	//TODO: Fix how padding should be handled (now that arg is no longer single string)
	last = (*icur)->arg;
	while (last->right != NULL)
		last = last->right;
	if ((id != padding && id != error && id != separator && id != exit_state) \
	&& ft_strlen(((*icur)->arg)->value) > 0)
		ft_add_token_to_comp(pad, &((last)->pad));
	return (id);
}

t_transition_code			sh_arg_pad_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_token				*pad;
	t_arg				*last;

	pad = *this;
	(void)icur;
	while (recognise_token_state(*this) == padding && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	// TODO: Fix how padding should be handled (now that arg is no longer single string)
	last = (*icur)->arg;
	while (last->right != NULL)
		last = last->right;
	if (id != padding && id != error && id != separator && id != exit_state)
		ft_add_token_to_comp(pad, &(last->pad));
	return (id);
}
