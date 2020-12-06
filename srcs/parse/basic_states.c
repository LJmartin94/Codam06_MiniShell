/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   basic_states.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 18:10:03 by limartin      #+#    #+#                 */
/*   Updated: 2021/01/05 10:26:33 by lindsay       ########   odam.nl         */
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
	t_arg				*last;
	t_arg				*new;

	if (ft_strlen(((*icur)->arg)->value) > 0 || \
	ft_strlen(((*icur)->arg)->type) > 0)
	{
		new = (t_arg *)e_malloc(sizeof(t_arg));
		ft_argconst(new);
		ft_add_arg(&(*icur)->arg, new);
	}
	last = (*icur)->arg;
	while (last->right != NULL)
		last = last->right;
	ft_add_token_to_comp((*this), &((last)->value));
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
	t_arg				*new;

	if (ft_strlen(((*icur)->arg)->value) > 0 || \
	ft_strlen(((*icur)->arg)->type) > 0)
	{
		new = (t_arg *)e_malloc(sizeof(t_arg));
		ft_argconst(new);
		ft_add_arg(&(*icur)->arg, new);
	}
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

	validate_option_flags(icur);
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
