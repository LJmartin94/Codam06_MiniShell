/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   basic_states.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 18:10:03 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/12 22:12:15 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "error.h"

t_transition_code	sh_cmd_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	ft_add_token_to_comp((*this), &((*icur)->cmd));
	*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_opt_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	//t_arg				*last;

	// last = (*icur)->arg;
	// while (last->right != NULL)
	// 	last = last->right;
	ft_add_token_to_comp((*this), &(((*icur)->arg)->value));
	//ft_add_token_to_comp((*this), &((*icur)->arg));
	*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_arg_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_arg				*last;

	last = (*icur)->arg;
	while (last->right != NULL)
		last = last->right;
	ft_add_token_to_comp((*this), &(last->value));
	*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_separator_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_icomp				*new_block;

	ft_add_token_to_comp((*this), &((*icur)->sep));
	*this = (*this)->next;
	while (recognise_token_state(*this) == padding && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	if (id != exit_state)
	{
		new_block = (t_icomp *)e_malloc(sizeof(t_icomp));
		ft_compconst(new_block);
		new_block->id = (*icur)->id + 1;
		ft_add_component(icur, new_block);
		*icur = (*icur)->right;
	}
	return (id);
}
