/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sq_exit_basic_states.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 18:10:03 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/28 11:53:53 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "error.h"

t_transition_code	sh_sq_exit_cmd_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	(void)icur;
	if (recognise_token_state(*this) == sq && *this)
		*this = (*this)->next;
	while (recognise_token_state(*this) == padding && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_sq_exit_option_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	int					valid;

	(void)icur;
	if (recognise_token_state(*this) == sq && *this)
		*this = (*this)->next;
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

t_transition_code	sh_sq_exit_arg_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	(void)icur;
	if (recognise_token_state(*this) == sq && *this)
		*this = (*this)->next;
	while (recognise_token_state(*this) == padding && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

// t_transition_code	sh_dq_argument_pad_state(t_token **this, t_icomp **icur)
// {
// 	t_transition_code	id;
// 	t_token				*tmp;

// 	tmp = *this;
// 	*this = (*this)->next;
// 	id = exit_state;
// 	if ((*this) != NULL)
// 		id = recognise_token_state(*this);
// 	if (id == arg)
// 		ft_add_token_to_comp((tmp), &((*icur)->arg));
// 	return (id);
// }

// t_transition_code	sh_dq_separator_state(t_token **this, t_icomp **icur)
// {
// 	t_transition_code	id;
// 	t_icomp				*new_block;

// 	ft_add_token_to_comp((*this), &((*icur)->sep));
// 	*this = (*this)->next;
// 	// while (recognise_token_state(*this) == padding && *this)
// 	// 	*this = (*this)->next;
// 	id = exit_state;
// 	if ((*this) != NULL)
// 		id = recognise_token_state(*this);
// 	if (id != exit_state)
// 	{
// 		new_block = (t_icomp *)e_malloc(sizeof(t_icomp));
// 		ft_compconst(new_block);
// 		new_block->id = (*icur)->id + 1;
// 		ft_add_component(icur, new_block);
// 		*icur = (*icur)->right;
// 	}
// 	return (id);
// }
