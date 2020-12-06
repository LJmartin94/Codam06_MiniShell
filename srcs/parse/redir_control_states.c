/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_control_states.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/27 15:02:47 by lindsay       #+#    #+#                 */
/*   Updated: 2021/01/06 11:57:01 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "error.h"

static t_redir		*new_last(t_redir *last)
{
	last->right = (t_redir *)e_malloc(sizeof(t_redir));
	ft_redirconst(last->right);
	(last->right)->left = last;
	last = last->right;
	return (last);
}

t_transition_code	sh_rd_entry_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_redir				*last;

	last = (*icur)->rdhead;
	while (last->right != NULL)
		last = last->right;
	if (ft_strlen((last)->file) > 0)
		last = new_last(last);
	id = recognise_token_state(*this);
	if (id == redir_out || id == dredir_out)
		ft_add_token_to_comp((*this), &((last)->type_out));
	if (id == redir_in)
		ft_add_token_to_comp((*this), &((last)->type_in));
	*this = (*this)->next;
	while (*this != NULL && recognise_token_state(*this) == padding)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	if (id == redir_out && ft_strlen(last->type_out) != 0)
		id = error;
	return (id);
}

//not sure about the below returning Arg state when it does...

t_transition_code	sh_rd_exit_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	if (id != padding && id != separator && id != exit_state)
		return (error);
	if (id == padding && \
	(ft_strlen((*icur)->arg->value) > 0 || ft_strlen((*icur)->arg->type) > 0))
		return (arg);
	if (id == padding && ft_strlen((*icur)->opt) > 0)
		return (opt);
	if (id == padding && ft_strlen((*icur)->cmd) > 0)
		return (cmd);
	if (id == padding || id == separator)
		return (id);
	return (id);
}
