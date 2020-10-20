/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   entry_state.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 18:10:03 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/20 16:36:08 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdio.h> //remove

t_transition_code sh_entry_state(t_token *this, t_icomp *icur)
{
	(void)icur; //Just to make it shut up about unused variables
	t_transition_code	id;

	id = recognise_token_state(this);
	printf("In entry state: |%s| seems to be |%d|\n", this->token, id);
	return (id);
}

t_transition_code sh_command_state(t_token *this, t_icomp *icur)
{
	(void)icur; //Just to make it shut up about unused variables
	t_transition_code	id;

	id = recognise_token_state(this);
	printf("In command state: |%s| seems to be |%d|\n", this->token, id);
	return (id);
}

t_transition_code sh_error_state(t_token *this, t_icomp *icur)
{
	(void)icur; //Just to make it shut up about unused variables
	t_transition_code	id;

	id = recognise_token_state(this);
	printf("In error state: |%s| seems to be |%d|\n", this->token, id);
	return (id);
}

t_transition_code sh_argument_state(t_token *this, t_icomp *icur)
{
	(void)icur; //Just to make it shut up about unused variables
	t_transition_code	id;

	id = recognise_token_state(this);
	printf("In argument state: |%s| seems to be |%d|\n", this->token, id);
	return (id);
}

t_transition_code sh_option_state(t_token *this, t_icomp *icur)
{
	(void)icur; //Just to make it shut up about unused variables
	t_transition_code	id;

	id = recognise_token_state(this);
	printf("In option state: |%s| seems to be |%d|\n", this->token, id);
	return (id);
}

t_transition_code sh_separator_state(t_token *this, t_icomp *icur)
{
	(void)icur; //Just to make it shut up about unused variables
	t_transition_code	id;

	id = recognise_token_state(this);
	printf("In separator state: |%s| seems to be |%d|\n", this->token, id);
	return (id);
}
