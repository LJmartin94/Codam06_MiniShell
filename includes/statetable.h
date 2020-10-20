/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   statetable.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 19:53:22 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/20 11:53:43 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATETABLE_H
# define STATETABLE_H

t_transition_obj const static g_shellstate_table[] =
{
	{sh_entry_state, state_command, sh_command_state},
	{sh_command_state, state_option, sh_option_state},
	{sh_command_state, state_arg, sh_argument_state},
	{sh_command_state, state_separator, sh_separator_state},
	{sh_option_state, state_option, sh_option_state},
	{sh_option_state, state_arg, sh_argument_state},
	{sh_option_state, state_separator, sh_separator_state},
	{sh_argument_state, state_arg, sh_argument_state},
	{sh_argument_state, state_separator, sh_separator_state},
	{sh_separator_state, state_entry, sh_entry_state},

	{sh_entry_state, state_padding, sh_entry_state},
	{sh_command_state, state_padding, sh_command_state},
	{sh_option_state, state_padding, sh_option_state},
	{sh_argument_state, state_padding, sh_argument_state},
	{sh_separator_state, state_padding, sh_separator_state},

	{sh_entry_state, state_error, sh_error_state},
	{sh_command_state, state_error, sh_error_state},
	{sh_option_state, state_error, sh_error_state},
	{sh_argument_state, state_error, sh_error_state},
	{sh_separator_state, state_error, sh_error_state}
};

#endif