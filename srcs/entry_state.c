/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   entry_state.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 18:10:03 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/20 14:33:35 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"//remove
#include "recognise_transition_table.h"
#include <stdio.h>

t_transition_code sh_entry_state(t_token *this, t_icomp *icur)
{
	(void)icur; //Just to make it shut up about unused variables
	int 				i;
	t_transition_code	id;

	i = 0;
	id = arg;
	while (i < recog_table_size)
	{
		if (ft_strncmp((g_tokenrecog_table[i]).to_compare, this->token, \
		ft_strlen(this->token)) == 0)
		{
			id = (&g_tokenrecog_table[i])->ret;
			break ;
		}
		i++;
	}
	printf("In entry state: |%s| seems to be |%d|\n", this->token, id);
	return (id);
}

t_transition_code sh_command_state(t_token *this, t_icomp *icur)
{
	ft_printf("In command state\n");
	(void)icur; //Just to make it shut up about unused variables
	if (this->token[0] == ' ')
	{
		return (padding);
	}
	else
		return (command); //I removed the pseudo function validate_command to make it compile
	return (error);
}

t_transition_code sh_error_state(t_token *this, t_icomp *icur)
{
	ft_printf("In error state\n");
	(void)icur; //Just to make it shut up about unused variables
	if (this->token[0] == ' ')
	{
		return (padding);
	}
	else
		return (command); //I removed the pseudo function validate_command to make it compile
	return (error);
}

t_transition_code sh_argument_state(t_token *this, t_icomp *icur)
{
	ft_printf("In argument state\n");
	(void)icur; //Just to make it shut up about unused variables
	if (this->token[0] == ' ')
	{
		return (padding);
	}
	else
		return (command); //I removed the pseudo function validate_command to make it compile
	return (error);
}

t_transition_code sh_option_state(t_token *this, t_icomp *icur)
{
	ft_printf("In option state\n");
	(void)icur; //Just to make it shut up about unused variables
	if (this->token[0] == ' ')
	{
		return (padding);
	}
	else
		return (command); //I removed the pseudo function validate_command to make it compile
	return (error);
}

t_transition_code sh_separator_state(t_token *this, t_icomp *icur)
{
	ft_printf("In separator state\n");
	(void)icur; //Just to make it shut up about unused variables
	if (this->token[0] == ' ')
	{
		return (padding);
	}
	else
		return (command); //I removed the pseudo function validate_command to make it compile
	return (error);
}
