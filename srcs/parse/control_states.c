/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   control_states.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 18:10:03 by limartin      #+#    #+#                 */
/*   Updated: 2020/12/12 17:06:00 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

//TODO: remove
#include "error.h"

t_transition_code	sh_entry_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	e_write(STDERR_FILENO, "Token in entry state: ", 22);
	print_tokens(*this);
	e_write(STDERR_FILENO, "\n", 1);
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

	e_write(STDERR_FILENO, "Token in error state: ", 22);
	print_tokens(*this);
	e_write(STDERR_FILENO, "\n", 1);
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

	validate_option_flags(icur);
	while (*this)
		*this = (*this)->next;
	id = exit_state;
	return (id);
}
