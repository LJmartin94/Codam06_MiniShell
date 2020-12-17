/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   control_states.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 18:10:03 by limartin      #+#    #+#                 */
/*   Updated: 2020/12/17 15:50:46 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "error.h"

t_transition_code	sh_entry_state(t_token **this, t_icomp **icur)
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

t_transition_code	sh_error_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	char				*error_type;
	t_icomp				*head;

	head = *icur;
	while (head->left != NULL)
		head = head->left;
	free(head->arg->type);
	error_type = ft_strdup("E");
	if (error_type == NULL)
		error_exit_errno();
	head->arg->type = error_type;
	syntax_error(STDERR_FILENO, this);
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
