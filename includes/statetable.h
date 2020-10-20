/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   statetable.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 19:53:22 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/20 14:30:28 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATETABLE_H
# define STATETABLE_H

static t_transition_obj const g_shellstate_table[] =
{
	{sh_entry_state, command, sh_command_state},
	{sh_command_state, option, sh_option_state},
	{sh_command_state, arg, sh_argument_state},
	{sh_command_state, separator, sh_separator_state},
	{sh_option_state, option, sh_option_state},
	{sh_option_state, arg, sh_argument_state},
	{sh_option_state, separator, sh_separator_state},
	{sh_argument_state, arg, sh_argument_state},
	{sh_argument_state, separator, sh_separator_state},
	{sh_separator_state, entry, sh_entry_state},

	{sh_entry_state, padding, sh_entry_state},
	{sh_command_state, padding, sh_command_state},
	{sh_option_state, padding, sh_option_state},
	{sh_argument_state, padding, sh_argument_state},
	{sh_separator_state, padding, sh_separator_state},
	{sh_error_state, padding, sh_error_state},

	{sh_entry_state, error, sh_error_state},
	{sh_command_state, error, sh_error_state},
	{sh_option_state, error, sh_error_state},
	{sh_argument_state, error, sh_error_state},
	{sh_separator_state, error, sh_error_state},
	{sh_error_state, error, sh_error_state}
};

#endif
