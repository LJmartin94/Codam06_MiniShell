/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   statetable.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 19:53:22 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/05 22:13:00 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATETABLE_H
# define STATETABLE_H

static t_transition_obj const g_shellstate_table[] =
{
	{sh_entry_state, padding, sh_entry_state},
	{sh_entry_state, error, sh_error_state},
	{sh_entry_state, dq, sh_dq_cmd_state},
	{sh_entry_state, sq, sh_sq_cmd_state},
	{sh_entry_state, backslash, sh_bs_cmd_state},
	{sh_entry_state, command, sh_command_state},
	{sh_entry_state, option, sh_command_state},
	{sh_entry_state, arg, sh_command_state},
	{sh_entry_state, separator, sh_error_state},
	{sh_entry_state, exit_state, sh_exit_state},

	{sh_command_state, padding, sh_command_state},
	{sh_command_state, error, sh_error_state},
	{sh_command_state, dq, sh_dq_option_state},
	{sh_command_state, sq, sh_sq_option_state},
	{sh_command_state, backslash, sh_bs_cmd_state},
	{sh_command_state, command, sh_argument_state},
	{sh_command_state, option, sh_option_state},
	{sh_command_state, arg, sh_argument_state},
	{sh_command_state, separator, sh_separator_state},
	{sh_command_state, exit_state, sh_exit_state},

	{sh_option_state, padding, sh_option_state},
	{sh_option_state, error, sh_error_state},
	{sh_option_state, dq, sh_dq_option_state},
	{sh_option_state, sq, sh_sq_option_state},
	{sh_option_state, backslash, sh_bs_option_state},
	{sh_option_state, command, sh_argument_state},
	{sh_option_state, option, sh_option_state},
	{sh_option_state, arg, sh_argument_state},
	{sh_option_state, separator, sh_separator_state},
	{sh_option_state, exit_state, sh_exit_state},

	{sh_argument_state, padding, sh_argument_state},
	{sh_argument_state, error, sh_error_state},
	{sh_argument_state, dq, sh_dq_arg_state},
	{sh_argument_state, sq, sh_sq_arg_state},
	{sh_argument_state, backslash, sh_bs_arg_state},
	{sh_argument_state, command, sh_argument_state},
	{sh_argument_state, option, sh_argument_state},
	{sh_argument_state, arg, sh_argument_state},
	{sh_argument_state, separator, sh_separator_state},
	{sh_argument_state, exit_state, sh_exit_state},

	{sh_separator_state, padding, sh_entry_state},
	{sh_separator_state, error, sh_error_state},
	{sh_separator_state, dq, sh_dq_cmd_state},
	{sh_separator_state, sq, sh_sq_cmd_state},
	{sh_separator_state, backslash, sh_bs_cmd_state},
	{sh_separator_state, command, sh_entry_state},
	{sh_separator_state, option, sh_entry_state},
	{sh_separator_state, arg, sh_entry_state},
	{sh_separator_state, separator, sh_error_state},
	{sh_separator_state, exit_state, sh_exit_state},

	{sh_dq_cmd_state, padding, sh_dq_cmd_state},
	{sh_dq_cmd_state, error, sh_error_state},
	{sh_dq_cmd_state, dq, sh_dq_exit_cmd_state},
	{sh_dq_cmd_state, sq, sh_dq_cmd_state},
	{sh_dq_cmd_state, backslash, sh_dq_cmd_state}, //dq requires separate backslash state
	{sh_dq_cmd_state, command, sh_dq_cmd_state},
	{sh_dq_cmd_state, option, sh_dq_cmd_state},
	{sh_dq_cmd_state, arg, sh_dq_cmd_state},
	{sh_dq_cmd_state, separator, sh_dq_cmd_state},
	{sh_dq_cmd_state, exit_state, sh_exit_state},

	{sh_dq_option_state, padding, sh_dq_option_state},
	{sh_dq_option_state, error, sh_error_state},
	{sh_dq_option_state, dq, sh_dq_exit_option_state},
	{sh_dq_option_state, sq, sh_dq_option_state},
	{sh_dq_option_state, backslash, sh_dq_option_state}, //dq requires separate backslash state
	{sh_dq_option_state, command, sh_dq_option_state},
	{sh_dq_option_state, option, sh_dq_option_state},
	{sh_dq_option_state, arg, sh_dq_option_state},
	{sh_dq_option_state, separator, sh_dq_option_state},
	{sh_dq_option_state, exit_state, sh_exit_state},

	{sh_dq_arg_state, padding, sh_dq_arg_state},
	{sh_dq_arg_state, error, sh_error_state},
	{sh_dq_arg_state, dq, sh_dq_exit_arg_state},
	{sh_dq_arg_state, sq, sh_dq_arg_state},
	{sh_dq_arg_state, backslash, sh_dq_arg_state}, //dq requires separate backslash state
	{sh_dq_arg_state, command, sh_dq_arg_state},
	{sh_dq_arg_state, option, sh_dq_arg_state},
	{sh_dq_arg_state, arg, sh_dq_arg_state},
	{sh_dq_arg_state, separator, sh_dq_arg_state},
	{sh_dq_arg_state, exit_state, sh_exit_state},

	{sh_dq_exit_cmd_state, padding, sh_command_state},
	{sh_dq_exit_cmd_state, error, sh_error_state},
	{sh_dq_exit_cmd_state, dq, sh_dq_option_state},
	{sh_dq_exit_cmd_state, sq, sh_sq_option_state},
	{sh_dq_exit_cmd_state, backslash, sh_bs_option_state},
	{sh_dq_exit_cmd_state, command, sh_argument_state},
	{sh_dq_exit_cmd_state, option, sh_option_state},
	{sh_dq_exit_cmd_state, arg, sh_argument_state},
	{sh_dq_exit_cmd_state, separator, sh_separator_state},
	{sh_dq_exit_cmd_state, exit_state, sh_exit_state},

	{sh_dq_exit_option_state, padding, sh_option_state},
	{sh_dq_exit_option_state, error, sh_error_state},
	{sh_dq_exit_option_state, dq, sh_dq_option_state},
	{sh_dq_exit_option_state, sq, sh_sq_option_state},
	{sh_dq_exit_option_state, backslash, sh_bs_option_state},
	{sh_dq_exit_option_state, command, sh_argument_state},
	{sh_dq_exit_option_state, option, sh_option_state},
	{sh_dq_exit_option_state, arg, sh_argument_state},
	{sh_dq_exit_option_state, separator, sh_separator_state},
	{sh_dq_exit_option_state, exit_state, sh_exit_state},

	{sh_dq_exit_arg_state, padding, sh_argument_state},
	{sh_dq_exit_arg_state, error, sh_error_state},
	{sh_dq_exit_arg_state, dq, sh_dq_arg_state},
	{sh_dq_exit_arg_state, sq, sh_sq_arg_state},
	{sh_dq_exit_arg_state, backslash, sh_bs_arg_state},
	{sh_dq_exit_arg_state, command, sh_argument_state},
	{sh_dq_exit_arg_state, option, sh_argument_state},
	{sh_dq_exit_arg_state, arg, sh_argument_state},
	{sh_dq_exit_arg_state, separator, sh_separator_state},
	{sh_dq_exit_arg_state, exit_state, sh_exit_state},

	{sh_sq_cmd_state, padding, sh_sq_cmd_state},
	{sh_sq_cmd_state, error, sh_error_state},
	{sh_sq_cmd_state, dq, sh_sq_cmd_state},
	{sh_sq_cmd_state, sq, sh_sq_exit_cmd_state},
	{sh_sq_cmd_state, backslash, sh_sq_cmd_state},
	{sh_sq_cmd_state, command, sh_sq_cmd_state},
	{sh_sq_cmd_state, option, sh_sq_cmd_state},
	{sh_sq_cmd_state, arg, sh_sq_cmd_state},
	{sh_sq_cmd_state, separator, sh_sq_cmd_state},
	{sh_sq_cmd_state, exit_state, sh_exit_state},

	{sh_sq_option_state, padding, sh_sq_option_state},
	{sh_sq_option_state, error, sh_error_state},
	{sh_sq_option_state, dq, sh_sq_option_state},
	{sh_sq_option_state, sq, sh_sq_exit_option_state},
	{sh_sq_option_state, backslash, sh_sq_option_state},
	{sh_sq_option_state, command, sh_sq_option_state},
	{sh_sq_option_state, option, sh_sq_option_state},
	{sh_sq_option_state, arg, sh_sq_option_state},
	{sh_sq_option_state, separator, sh_sq_option_state},
	{sh_sq_option_state, exit_state, sh_exit_state},

	{sh_sq_arg_state, padding, sh_sq_arg_state},
	{sh_sq_arg_state, error, sh_error_state},
	{sh_sq_arg_state, dq, sh_sq_arg_state},
	{sh_sq_arg_state, sq, sh_sq_exit_arg_state},
	{sh_sq_arg_state, backslash, sh_sq_arg_state},
	{sh_sq_arg_state, command, sh_sq_arg_state},
	{sh_sq_arg_state, option, sh_sq_arg_state},
	{sh_sq_arg_state, arg, sh_sq_arg_state},
	{sh_sq_arg_state, separator, sh_sq_arg_state},
	{sh_sq_arg_state, exit_state, sh_exit_state},

	{sh_sq_exit_cmd_state, padding, sh_command_state},
	{sh_sq_exit_cmd_state, error, sh_error_state},
	{sh_sq_exit_cmd_state, dq, sh_dq_option_state},
	{sh_sq_exit_cmd_state, sq, sh_sq_option_state},
	{sh_sq_exit_cmd_state, backslash, sh_bs_option_state},
	{sh_sq_exit_cmd_state, command, sh_argument_state},
	{sh_sq_exit_cmd_state, option, sh_option_state},
	{sh_sq_exit_cmd_state, arg, sh_argument_state},
	{sh_sq_exit_cmd_state, separator, sh_separator_state},
	{sh_sq_exit_cmd_state, exit_state, sh_exit_state},

	{sh_sq_exit_option_state, padding, sh_option_state},
	{sh_sq_exit_option_state, error, sh_error_state},
	{sh_sq_exit_option_state, dq, sh_dq_option_state},
	{sh_sq_exit_option_state, sq, sh_sq_option_state},
	{sh_sq_exit_option_state, backslash, sh_bs_option_state}, 
	{sh_sq_exit_option_state, command, sh_argument_state},
	{sh_sq_exit_option_state, option, sh_option_state},
	{sh_sq_exit_option_state, arg, sh_argument_state},
	{sh_sq_exit_option_state, separator, sh_separator_state},
	{sh_sq_exit_option_state, exit_state, sh_exit_state},

	{sh_sq_exit_arg_state, padding, sh_argument_state},
	{sh_sq_exit_arg_state, error, sh_error_state},
	{sh_sq_exit_arg_state, dq, sh_dq_arg_state},
	{sh_sq_exit_arg_state, sq, sh_sq_arg_state},
	{sh_sq_exit_arg_state, backslash, sh_bs_arg_state},
	{sh_sq_exit_arg_state, command, sh_argument_state},
	{sh_sq_exit_arg_state, option, sh_argument_state},
	{sh_sq_exit_arg_state, arg, sh_argument_state},
	{sh_sq_exit_arg_state, separator, sh_separator_state},
	{sh_sq_exit_arg_state, exit_state, sh_exit_state},

	{sh_bs_cmd_state, padding, sh_command_state},
	{sh_bs_cmd_state, error, sh_error_state},
	{sh_bs_cmd_state, dq, sh_dq_option_state},
	{sh_bs_cmd_state, sq, sh_sq_option_state},
	{sh_bs_cmd_state, backslash, sh_bs_cmd_state},
	{sh_bs_cmd_state, command, sh_command_state},
	{sh_bs_cmd_state, option, sh_option_state},
	{sh_bs_cmd_state, arg, sh_command_state},
	{sh_bs_cmd_state, separator, sh_separator_state},
	{sh_bs_cmd_state, exit_state, sh_exit_state},

	{sh_bs_option_state, padding, sh_option_state},
	{sh_bs_option_state, error, sh_error_state},
	{sh_bs_option_state, dq, sh_dq_option_state},
	{sh_bs_option_state, sq, sh_sq_option_state},
	{sh_bs_option_state, backslash, sh_bs_option_state},
	{sh_bs_option_state, command, sh_argument_state},
	{sh_bs_option_state, option, sh_option_state},
	{sh_bs_option_state, arg, sh_argument_state},
	{sh_bs_option_state, separator, sh_separator_state},
	{sh_bs_option_state, exit_state, sh_exit_state},

	{sh_bs_arg_state, padding, sh_argument_state},
	{sh_bs_arg_state, error, sh_error_state},
	{sh_bs_arg_state, dq, sh_dq_arg_state},
	{sh_bs_arg_state, sq, sh_sq_arg_state},
	{sh_bs_arg_state, backslash, sh_bs_arg_state},
	{sh_bs_arg_state, command, sh_argument_state},
	{sh_bs_arg_state, option, sh_argument_state},
	{sh_bs_arg_state, arg, sh_argument_state},
	{sh_bs_arg_state, separator, sh_separator_state},
	{sh_bs_arg_state, exit_state, sh_exit_state},

	{sh_error_state, padding, sh_error_state},
	{sh_error_state, error, sh_error_state},
	{sh_error_state, dq, sh_error_state},
	{sh_error_state, sq, sh_error_state},
	{sh_error_state, backslash, sh_error_state},
	{sh_error_state, command, sh_error_state},
	{sh_error_state, option, sh_error_state},
	{sh_error_state, arg, sh_error_state},
	{sh_error_state, separator, sh_error_state},
	{sh_error_state, exit_state, sh_exit_state},

	{sh_exit_state, padding, sh_exit_state},
	{sh_exit_state, error, sh_exit_state},
	{sh_exit_state, dq, sh_exit_state},
	{sh_exit_state, sq, sh_exit_state},
	{sh_exit_state, backslash, sh_exit_state},
	{sh_exit_state, command, sh_exit_state},
	{sh_exit_state, option, sh_exit_state},
	{sh_exit_state, arg, sh_exit_state},
	{sh_exit_state, separator, sh_exit_state},
	{sh_exit_state, exit_state, sh_exit_state}
};

#endif
