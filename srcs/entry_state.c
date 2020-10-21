/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   entry_state.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 18:10:03 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/21 13:05:48 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdio.h> //remove

t_transition_code sh_entry_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	printf("In state,\nicur =	[%p]\n*icur =	[%p]\n&(**icur) =	[%p]\n", icur, *icur, &(**icur));

	(void)icur;
	id = recognise_token_state(*this);
	if ((*this))
		printf("In entry state: |%s| seems to be |%d|\n", (*this)->token, id);
	return (id);
}

t_transition_code sh_command_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	ft_add_token_to_comp((*this), &((*icur)->cmd));
	*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	if ((*this))
		printf("In command state: |%s| seems to be |%d|\n", (*this)->token, id);
	return (id);
}

t_transition_code sh_error_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	(void)icur;
	*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	if ((*this))
		printf("In error state: |%s| seems to be |%d|\n", (*this)->token, id);
	return (id);
}

t_transition_code sh_argument_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	ft_add_token_to_comp((*this), &((*icur)->arg));
	*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	if ((*this))
		printf("In argument state: |%s| seems to be |%d|\n", (*this)->token, id);
	printf("[%p] Arg block (before exit):\nCMD: |%s|\nOPT: |%s|\nARG: |%s|\n", (*icur), (*icur)->cmd, (*icur)->opt, (*icur)->arg);
	return (id);
}

t_transition_code sh_option_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	ft_add_token_to_comp((*this), &((*icur)->opt));
	*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	if ((*this))
		printf("In option state: |%s| seems to be |%d|\n", (*this)->token, id);
	return (id);
}

t_transition_code sh_separator_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_icomp				*new_block;

	ft_add_token_to_comp((*this), &((*icur)->sep));
	*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	printf("[%p] Head block:\nCMD: |%s|\nOPT: |%s|\nARG: |%s|\nSEP: |%s|\nPTR: |%p|\n", (*icur), (*icur)->cmd, (*icur)->opt, (*icur)->arg, (*icur)->sep, (*icur)->next);
	if (id != exit_state)
	{
		new_block = (t_icomp *)malloc(sizeof(t_icomp));
		ft_compconst(new_block);
		ft_add_component(icur, new_block);
		printf("[%p] Linked head block:\nCMD: |%s|\nOPT: |%s|\nARG: |%s|\nSEP: |%s|\nPTR: |%p|\n", (*icur), (*icur)->cmd, (*icur)->opt, (*icur)->arg, (*icur)->sep, (*icur)->next);
		*icur = (*icur)->next;
		printf("[%p] icur block after move:\nCMD: |%s|\nOPT: |%s|\nARG: |%s|\nSEP: |%s|\nPTR: |%p|\n", (*icur), (*icur)->cmd, (*icur)->opt, (*icur)->arg, (*icur)->sep, (*icur)->next);
		//icur = &((*icur)->next);
	}
	if ((*this))
		printf("In separator state: |%s| seems to be |%d|\n", (*this)->token, id);
	return (id);
}

t_transition_code sh_exit_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;

	(void)icur;
	(void)this;
	id = exit_state;
	printf("In exit state: |%d|\n", id);
	printf("[%p] Exit block:\nCMD: |%s|\nOPT: |%s|\nARG: |%s|\n", (*icur), (*icur)->cmd, (*icur)->opt, (*icur)->arg);
	//printf("Comp block:\nCMD: |%s|\nOPT: |%s|\nARG: |%s|\nSEP: |%s|\n", (*icur)->cmd, (*icur)->opt, (*icur)->arg, (*icur)->sep);
	return (id);
}