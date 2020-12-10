/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   control_states.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 18:10:03 by limartin      #+#    #+#                 */
/*   Updated: 2020/12/10 22:21:27 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_transition_code	sh_entry_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	write(1, "ENTRY\n", 6);
	(void)icur;
	while (recognise_token_state(*this) == padding && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_error_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	write(1, "ERROR\n", 6);
	(void)icur;
	// if (*this != NULL)
	// 	*this = (*this)->next;
	// while (recognise_token_state(*this) == padding && *this)
	// 	*this = (*this)->next;
	syntax_error(STDERR_FILENO, this);
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	id = exit_state;
	return (id);
}

t_transition_code	sh_exit_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	write(1, "EXIT\n", 5);
	validate_option_flags(icur);
	while (*this)
		*this = (*this)->next;
	id = exit_state;
	return (id);
}
