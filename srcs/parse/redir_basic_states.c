/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_basic_states.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 18:07:18 by lindsay       #+#    #+#                 */
/*   Updated: 2020/12/02 20:09:38 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//basic

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

//bs basic

t_transition_code	sh_bs_cmd_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

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

//dq basic (&exit?)

t_transition_code	sh_dq_cmd_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	if (recognise_token_state(*this) == dq && *this)
		*this = (*this)->next;
	if (recognise_token_state(*this) != backslash && \
	recognise_token_state(*this) != dq && *this)
	{
		ft_add_token_to_comp((*this), &((*icur)->cmd));
		*this = (*this)->next;
	}
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

t_transition_code	sh_dq_exit_cmd_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	(void)icur;
	if (recognise_token_state(*this) == dq && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

//dq bs basic

t_transition_code	sh_dq_bs_cmd_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

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

//sq basic (&exit?)

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

t_transition_code	sh_sq_exit_cmd_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	(void)icur;
	if (recognise_token_state(*this) == sq && *this)
		*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	return (id);
}

