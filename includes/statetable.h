/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   statetable.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 19:53:22 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/25 14:11:34 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATETABLE_H
# define STATETABLE_H

static t_transition_obj const g_shellstate_table[] =
{
	{sh_entry_state, padding, sh_entry_state},
	{sh_entry_state, error, sh_error_state},
	{sh_entry_state, dq, sh_dq_command_state},
	{sh_entry_state, command, sh_command_state},
	{sh_entry_state, option, sh_command_state},
	{sh_entry_state, arg, sh_command_state},
	{sh_entry_state, separator, sh_error_state},
	{sh_entry_state, exit_state, sh_exit_state},

	{sh_command_state, padding, sh_command_state},
	{sh_command_state, error, sh_error_state},
	{sh_command_state, dq, sh_dq_option_state},
	{sh_command_state, command, sh_argument_state},
	{sh_command_state, option, sh_option_state},
	{sh_command_state, arg, sh_argument_state},
	{sh_command_state, separator, sh_separator_state},
	{sh_command_state, exit_state, sh_exit_state},

	{sh_option_state, padding, sh_option_state},
	{sh_option_state, error, sh_error_state},
	{sh_option_state, dq, sh_dq_option_state}, //not sure
	{sh_option_state, command, sh_argument_state},
	{sh_option_state, option, sh_option_state},
	{sh_option_state, arg, sh_argument_state},
	{sh_option_state, separator, sh_separator_state},
	{sh_option_state, exit_state, sh_exit_state},

	{sh_argument_state, padding, sh_argument_pad_state},
	{sh_argument_state, error, sh_error_state},
	{sh_argument_state, dq, sh_dq_argument_state}, //not sure
	{sh_argument_state, command, sh_argument_state},
	{sh_argument_state, option, sh_argument_state},
	{sh_argument_state, arg, sh_argument_state},
	{sh_argument_state, separator, sh_separator_state},
	{sh_argument_state, exit_state, sh_exit_state},

	{sh_argument_pad_state, padding, sh_argument_pad_state},
	{sh_argument_pad_state, error, sh_error_state},
	{sh_argument_pad_state, dq, sh_dq_argument_state}, //not sure
	{sh_argument_pad_state, command, sh_argument_state},
	{sh_argument_pad_state, option, sh_argument_state},
	{sh_argument_pad_state, arg, sh_argument_state},
	{sh_argument_pad_state, separator, sh_separator_state},
	{sh_argument_pad_state, exit_state, sh_exit_state},

	{sh_separator_state, padding, sh_entry_state},
	{sh_separator_state, error, sh_error_state},
	{sh_separator_state, dq, sh_dq_command_state},
	{sh_separator_state, command, sh_entry_state},
	{sh_separator_state, option, sh_entry_state},
	{sh_separator_state, arg, sh_entry_state},
	{sh_separator_state, separator, sh_error_state},
	{sh_separator_state, exit_state, sh_exit_state},

	
	{sh_dq_command_state, padding, sh_dq_command_state},
	{sh_dq_command_state, error, sh_error_state},
	{sh_dq_command_state, dq, sh_dq_exit_command_state},
	{sh_dq_command_state, command, sh_dq_command_state},
	{sh_dq_command_state, option, sh_dq_command_state},
	{sh_dq_command_state, arg, sh_dq_command_state},
	{sh_dq_command_state, separator, sh_dq_command_state},
	{sh_dq_command_state, exit_state, sh_exit_state},
	
	{sh_dq_option_state, padding, sh_dq_option_state},
	{sh_dq_option_state, error, sh_error_state},
	{sh_dq_option_state, dq, sh_dq_exit_option_state},
	{sh_dq_option_state, command, sh_dq_option_state},
	{sh_dq_option_state, option, sh_dq_option_state},
	{sh_dq_option_state, arg, sh_dq_option_state},
	{sh_dq_option_state, separator, sh_dq_option_state},
	{sh_dq_option_state, exit_state, sh_exit_state},

	{sh_dq_argument_state, padding, sh_dq_argument_state},
	{sh_dq_argument_state, error, sh_error_state},
	{sh_dq_argument_state, dq, sh_dq_exit_argument_state},
	{sh_dq_argument_state, command, sh_dq_argument_state},
	{sh_dq_argument_state, option, sh_dq_argument_state},
	{sh_dq_argument_state, arg, sh_dq_argument_state},
	{sh_dq_argument_state, separator, sh_dq_argument_state},
	{sh_dq_argument_state, exit_state, sh_exit_state},

	
	{sh_dq_exit_command_state, padding, sh_command_state},
	{sh_dq_exit_command_state, error, sh_error_state},
	{sh_dq_exit_command_state, dq, sh_dq_option_state}, //not sure
	{sh_dq_exit_command_state, command, sh_argument_state},
	{sh_dq_exit_command_state, option, sh_option_state},
	{sh_dq_exit_command_state, arg, sh_argument_state},
	{sh_dq_exit_command_state, separator, sh_separator_state},
	{sh_dq_exit_command_state, exit_state, sh_exit_state},

	{sh_dq_exit_option_state, padding, sh_option_state},
	{sh_dq_exit_option_state, error, sh_error_state},
	{sh_dq_exit_option_state, dq, sh_dq_option_state}, //not sure
	{sh_dq_exit_option_state, command, sh_argument_state},
	{sh_dq_exit_option_state, option, sh_option_state},
	{sh_dq_exit_option_state, arg, sh_argument_state},
	{sh_dq_exit_option_state, separator, sh_separator_state},
	{sh_dq_exit_option_state, exit_state, sh_exit_state},

	{sh_dq_exit_argument_state, padding, sh_argument_pad_state},
	{sh_dq_exit_argument_state, error, sh_error_state},
	{sh_dq_exit_argument_state, dq, sh_dq_argument_state}, //not sure
	{sh_dq_exit_argument_state, command, sh_argument_state},
	{sh_dq_exit_argument_state, option, sh_argument_state},
	{sh_dq_exit_argument_state, arg, sh_argument_state},
	{sh_dq_exit_argument_state, separator, sh_separator_state},
	{sh_dq_exit_argument_state, exit_state, sh_exit_state},


	{sh_error_state, padding, sh_error_state},
	{sh_error_state, error, sh_error_state},
	{sh_error_state, dq, sh_error_state},
	{sh_error_state, command, sh_error_state},
	{sh_error_state, option, sh_error_state},
	{sh_error_state, arg, sh_error_state},
	{sh_error_state, separator, sh_error_state},
	{sh_error_state, exit_state, sh_exit_state},

	{sh_exit_state, padding, sh_exit_state},
	{sh_exit_state, error, sh_exit_state},
	{sh_exit_state, dq, sh_exit_state},
	{sh_exit_state, command, sh_exit_state},
	{sh_exit_state, option, sh_exit_state},
	{sh_exit_state, arg, sh_exit_state},
	{sh_exit_state, separator, sh_exit_state},
	{sh_exit_state, exit_state, sh_exit_state}
};

#endif
