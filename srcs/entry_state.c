/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   entry_state.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 18:10:03 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/19 21:36:29 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"//remove

t_transition_code sh_entry_state(t_token *this, t_icomp *icur)
{
	ft_printf("In entry state\n");
	(void)icur; //Just to make it shut up about unused variables
	if (this->token[0] == ' ')
	{
		return (state_padding);
	}
	else
		return (state_command); //I removed the pseudo function validate_command to make it compile
	return (state_error);
}

t_transition_code sh_command_state(t_token *this, t_icomp *icur)
{
	ft_printf("In command state\n");
	(void)icur; //Just to make it shut up about unused variables
	if (this->token[0] == ' ')
	{
		return (state_padding);
	}
	else
		return (state_command); //I removed the pseudo function validate_command to make it compile
	return (state_error);
}

t_transition_code sh_error_state(t_token *this, t_icomp *icur)
{
	ft_printf("In error state\n");
	(void)icur; //Just to make it shut up about unused variables
	if (this->token[0] == ' ')
	{
		return (state_padding);
	}
	else
		return (state_command); //I removed the pseudo function validate_command to make it compile
	return (state_error);
}
