/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_control_states.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/27 15:02:47 by lindsay       #+#    #+#                 */
/*   Updated: 2020/11/29 18:05:21 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_transition_code	sh_rd_entry_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_redir				*last;
	t_redir				*new;

	if (ft_strlen(((*icur)->rdhead)->file) > 0)
	{
		new = (t_redir *)e_malloc(sizeof(t_redir));
		ft_redirconst(new);
		ft_add_redir(&(*icur)->rdhead, new);
	}
	last = (*icur)->rdhead;
	while (last->right != NULL)
		last = last->right;
	id = recognise_token_state(*this);
	if (id == redir_out || id == dredir_out)
		ft_add_token_to_comp((*this), &((last)->type_out));
	if (id == redir_in)
		ft_add_token_to_comp((*this), &((last)->type_in));
	*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	if (id == redir_out && ft_strlen(last->type_out) != 0)
		id = error;
	return (id);
}

t_transition_code	sh_rd_exit_state(t_token **this, t_icomp **icur)
{
	//enter this state if encountered padding or separator.
	// should only be accessed from a redirection-processing state, 
	// either on pad or on separator (or on exit if not enough valid tokens)
	// dont skip whatever token sent you, just redirect to the correct state
	t_transition_code	id;

	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	if (id != padding && id != separator && id != exit_state)
		return (error);
	if (id == padding && ft_strlen((*icur)->arg->value > 0))
		return (arg);
	if (id == padding && ft_strlen((*icur)->opt > 0))
		return (opt);
	if (id == padding && ft_strlen((*icur)->cmd > 0))
		return (cmd);
	if (id == padding || id == separator)
		return (id);
	return (id);
}
