/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sq_basic_states.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 18:10:03 by limartin      #+#    #+#                 */
/*   Updated: 2020/12/06 17:05:21 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "error.h"

t_transition_code	sh_sq_cmd_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	if (recognise_token_state(*this) == sq && *this)
		*this = (*this)->next;
	if (recognise_token_state(*this) != sq && *this)
	{
		ft_add_token_to_comp((*this), &((*icur)->cmd));
		*this = (*this)->next;
	}
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

static void			sh_sq_arg_open_state(t_token **this, t_icomp **icur)
{
	t_arg	*new;

	if (ft_strlen(((*icur)->arg)->value) > 0 || \
	ft_strlen(((*icur)->arg)->type) > 0)
	{
		new = (t_arg *)e_malloc(sizeof(t_arg));
		ft_argconst(new);
		ft_add_arg(&(*icur)->arg, new);
	}
	new = (*icur)->arg;
	while (new->right != NULL)
		new = new->right;
	free(new->type);
	new->type = ft_strdup("\'");
	if (new->type == NULL)
		error_exit_errno();
	*this = (*this)->next;
}

t_transition_code	sh_sq_opt_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_arg				*last;

	if (recognise_token_state(*this) == sq && *this)
		sh_sq_arg_open_state(this, icur);
	last = (*icur)->arg;
	while (last->right != NULL)
		last = last->right;
	if (recognise_token_state(*this) != sq && *this)
	{
		ft_add_token_to_comp((*this), &((last)->value));
		*this = (*this)->next;
	}
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_sq_arg_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_arg				*last;

	if (recognise_token_state(*this) == sq && *this)
		sh_sq_arg_open_state(this, icur);
	last = (*icur)->arg;
	while (last->right != NULL)
		last = last->right;
	if (recognise_token_state(*this) != sq && *this)
	{
		ft_add_token_to_comp((*this), &((last)->value));
		*this = (*this)->next;
	}
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}
