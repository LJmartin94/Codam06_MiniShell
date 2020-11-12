/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   basic_pad_states.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 13:30:27 by lindsay       #+#    #+#                 */
/*   Updated: 2020/11/08 13:54:06 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_transition_code	sh_cmd_pad_state(t_token **this, t_icomp **icur)
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

t_transition_code	sh_opt_pad_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	int					valid;
	t_token				*pad;

	pad = *this;
	valid = validate_option_flags(icur);
	while (recognise_token_state(*this) == padding && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	if (id == opt && valid == 0)
		id = arg;
	if ((id != padding && id != error && id != separator && id != exit_state) \
	&& ft_strlen((*icur)->arg) > 0)
		ft_add_token_to_comp(pad, &((*icur)->arg));
	return (id);
}

t_transition_code	sh_arg_pad_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_token				*pad;

	pad = *this;
	while (recognise_token_state(*this) == padding && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	if (id != padding && id != error && id != separator && id != exit_state)
		ft_add_token_to_comp(pad, &((*icur)->arg));
	return (id);
}