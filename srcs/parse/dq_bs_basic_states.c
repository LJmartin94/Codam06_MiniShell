/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dq_bs_basic_states.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/08 16:22:46 by limartin      #+#    #+#                 */
/*   Updated: 2021/01/14 15:41:59 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "error.h"

static int			handle_backslash(t_token **this, char **field)
{
	char c;

	if (*this && recognise_token_state(*this) == backslash && (*this)->next)
	{
		c = (*this)->next->token[0];
		if (c == '"' || c == '$' || c == '`' || c == '\\')
			return (1);
		else
			ft_add_token_to_comp((*this), field);
	}
	return (0);
}

static int			handle_backslash(t_token **this, char **field)
{
	char c;

	if (*this && recognise_token_state(*this) == backslash && (*this)->next)
	{
		c = (*this)->next->token[0];
		if (c == '"' || c == '$' || c == '`' || c == '\\')
			return (1);
		else
			ft_add_token_to_comp((*this), field);
	}
	return (0);
}

t_transition_code	sh_dq_bs_cmd_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	handle_backslash(this, &((*icur)->cmd));
	if (recognise_token_state(*this) == backslash && *this)
		*this = (*this)->next;
	if ((*this) != NULL)
	{
		ft_add_token_to_comp((*this), &((*icur)->cmd));
		*this = (*this)->next;
	}
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

static void			sh_dq_bs_arg_link_state(t_token **this, t_icomp **icur)
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
	new->type = ft_strdup("\"\\");
	if (new->type == NULL)
		error_exit_errno();
	handle_backslash(this, &((new)->value));
	*this = (*this)->next;
}

t_transition_code	sh_dq_bs_opt_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_arg				*last;

	if (recognise_token_state(*this) == backslash && *this)
		sh_dq_bs_arg_link_state(this, icur);
	last = (*icur)->arg;
	while (last->right != NULL)
		last = last->right;
	if ((*this) != NULL)
	{
		ft_add_token_to_comp((*this), &((last)->value));
		*this = (*this)->next;
	}
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_dq_bs_arg_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_arg				*last;

	if (recognise_token_state(*this) == backslash && *this)
		sh_dq_bs_arg_link_state(this, icur);
	last = (*icur)->arg;
	while (last->right != NULL)
		last = last->right;
	if ((*this) != NULL)
	{
		ft_add_token_to_comp((*this), &((last)->value));
		*this = (*this)->next;
	}
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}
