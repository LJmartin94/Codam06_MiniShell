/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   statetable.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 19:53:22 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/07 18:49:41 by limartin      ########   odam.nl         */
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
	{sh_entry_state, cmd, sh_cmd_state},
	{sh_entry_state, opt, sh_cmd_state},
	{sh_entry_state, arg, sh_cmd_state},
	{sh_entry_state, separator, sh_error_state},
	{sh_entry_state, exit_state, sh_exit_state},

	{sh_cmd_state, padding, sh_cmd_pad_state},
	{sh_cmd_state, error, sh_error_state},
	{sh_cmd_state, dq, sh_dq_cmd_state},
	{sh_cmd_state, sq, sh_sq_cmd_state},
	{sh_cmd_state, backslash, sh_bs_cmd_state},
	{sh_cmd_state, cmd, sh_cmd_state},
	{sh_cmd_state, opt, sh_cmd_state},
	{sh_cmd_state, arg, sh_cmd_state},
	{sh_cmd_state, separator, sh_separator_state},
	{sh_cmd_state, exit_state, sh_exit_state},

	{sh_cmd_pad_state, padding, sh_cmd_pad_state},
	{sh_cmd_pad_state, error, sh_error_state},
	{sh_cmd_pad_state, dq, sh_dq_opt_state},
	{sh_cmd_pad_state, sq, sh_sq_opt_state},
	{sh_cmd_pad_state, backslash, sh_bs_opt_state},
	{sh_cmd_pad_state, cmd, sh_arg_state},
	{sh_cmd_pad_state, opt, sh_opt_state},
	{sh_cmd_pad_state, arg, sh_arg_state},
	{sh_cmd_pad_state, separator, sh_separator_state},
	{sh_cmd_pad_state, exit_state, sh_exit_state},

	{sh_opt_state, padding, sh_opt_pad_state},
	{sh_opt_state, error, sh_error_state},
	{sh_opt_state, dq, sh_dq_opt_state},
	{sh_opt_state, sq, sh_sq_opt_state},
	{sh_opt_state, backslash, sh_bs_opt_state},
	{sh_opt_state, cmd, sh_opt_state},
	{sh_opt_state, opt, sh_opt_state},
	{sh_opt_state, arg, sh_opt_state},
	{sh_opt_state, separator, sh_separator_state},
	{sh_opt_state, exit_state, sh_exit_state},

	{sh_opt_pad_state, padding, sh_opt_pad_state},
	{sh_opt_pad_state, error, sh_error_state},
	{sh_opt_pad_state, dq, sh_dq_opt_state},
	{sh_opt_pad_state, sq, sh_sq_opt_state},
	{sh_opt_pad_state, backslash, sh_bs_opt_state},
	{sh_opt_pad_state, cmd, sh_arg_state},
	{sh_opt_pad_state, opt, sh_opt_state},
	{sh_opt_pad_state, arg, sh_arg_state},
	{sh_opt_pad_state, separator, sh_separator_state},
	{sh_opt_pad_state, exit_state, sh_exit_state},

	{sh_arg_state, padding, sh_arg_pad_state},
	{sh_arg_state, error, sh_error_state},
	{sh_arg_state, dq, sh_dq_arg_state},
	{sh_arg_state, sq, sh_sq_arg_state},
	{sh_arg_state, backslash, sh_bs_arg_state},
	{sh_arg_state, cmd, sh_arg_state},
	{sh_arg_state, opt, sh_arg_state},
	{sh_arg_state, arg, sh_arg_state},
	{sh_arg_state, separator, sh_separator_state},
	{sh_arg_state, exit_state, sh_exit_state},

	{sh_arg_pad_state, padding, sh_arg_pad_state},
	{sh_arg_pad_state, error, sh_error_state},
	{sh_arg_pad_state, dq, sh_dq_arg_state},
	{sh_arg_pad_state, sq, sh_sq_arg_state},
	{sh_arg_pad_state, backslash, sh_bs_arg_state},
	{sh_arg_pad_state, cmd, sh_arg_state},
	{sh_arg_pad_state, opt, sh_arg_state},
	{sh_arg_pad_state, arg, sh_arg_state},
	{sh_arg_pad_state, separator, sh_separator_state},
	{sh_arg_pad_state, exit_state, sh_exit_state},

	{sh_separator_state, padding, sh_entry_state},
	{sh_separator_state, error, sh_error_state},
	{sh_separator_state, dq, sh_dq_cmd_state},
	{sh_separator_state, sq, sh_sq_cmd_state},
	{sh_separator_state, backslash, sh_bs_cmd_state},
	{sh_separator_state, cmd, sh_entry_state},
	{sh_separator_state, opt, sh_entry_state},
	{sh_separator_state, arg, sh_entry_state},
	{sh_separator_state, separator, sh_error_state},
	{sh_separator_state, exit_state, sh_exit_state},

	{sh_dq_cmd_state, padding, sh_dq_cmd_state},
	{sh_dq_cmd_state, error, sh_error_state},
	{sh_dq_cmd_state, dq, sh_dq_exit_cmd_state},
	{sh_dq_cmd_state, sq, sh_dq_cmd_state},
	{sh_dq_cmd_state, backslash, sh_dq_cmd_state}, //dq requires separate backslash state
	{sh_dq_cmd_state, cmd, sh_dq_cmd_state},
	{sh_dq_cmd_state, opt, sh_dq_cmd_state},
	{sh_dq_cmd_state, arg, sh_dq_cmd_state},
	{sh_dq_cmd_state, separator, sh_dq_cmd_state},
	{sh_dq_cmd_state, exit_state, sh_exit_state},

	{sh_dq_opt_state, padding, sh_dq_opt_state},
	{sh_dq_opt_state, error, sh_error_state},
	{sh_dq_opt_state, dq, sh_dq_exit_opt_state},
	{sh_dq_opt_state, sq, sh_dq_opt_state},
	{sh_dq_opt_state, backslash, sh_dq_opt_state}, //dq requires separate backslash state
	{sh_dq_opt_state, cmd, sh_dq_opt_state},
	{sh_dq_opt_state, opt, sh_dq_opt_state},
	{sh_dq_opt_state, arg, sh_dq_opt_state},
	{sh_dq_opt_state, separator, sh_dq_opt_state},
	{sh_dq_opt_state, exit_state, sh_exit_state},

	{sh_dq_arg_state, padding, sh_dq_arg_state},
	{sh_dq_arg_state, error, sh_error_state},
	{sh_dq_arg_state, dq, sh_dq_exit_arg_state},
	{sh_dq_arg_state, sq, sh_dq_arg_state},
	{sh_dq_arg_state, backslash, sh_dq_arg_state}, //dq requires separate backslash state
	{sh_dq_arg_state, cmd, sh_dq_arg_state},
	{sh_dq_arg_state, opt, sh_dq_arg_state},
	{sh_dq_arg_state, arg, sh_dq_arg_state},
	{sh_dq_arg_state, separator, sh_dq_arg_state},
	{sh_dq_arg_state, exit_state, sh_exit_state},

	{sh_dq_exit_cmd_state, padding, sh_cmd_pad_state},
	{sh_dq_exit_cmd_state, error, sh_error_state},
	{sh_dq_exit_cmd_state, dq, sh_dq_cmd_state},
	{sh_dq_exit_cmd_state, sq, sh_sq_cmd_state},
	{sh_dq_exit_cmd_state, backslash, sh_bs_cmd_state},
	{sh_dq_exit_cmd_state, cmd, sh_cmd_state},
	{sh_dq_exit_cmd_state, opt, sh_cmd_state},
	{sh_dq_exit_cmd_state, arg, sh_cmd_state},
	{sh_dq_exit_cmd_state, separator, sh_separator_state},
	{sh_dq_exit_cmd_state, exit_state, sh_exit_state},

	{sh_dq_exit_opt_state, padding, sh_opt_pad_state},
	{sh_dq_exit_opt_state, error, sh_error_state},
	{sh_dq_exit_opt_state, dq, sh_dq_opt_state},
	{sh_dq_exit_opt_state, sq, sh_sq_opt_state},
	{sh_dq_exit_opt_state, backslash, sh_bs_opt_state},
	{sh_dq_exit_opt_state, cmd, sh_opt_state},
	{sh_dq_exit_opt_state, opt, sh_opt_state},
	{sh_dq_exit_opt_state, arg, sh_opt_state},
	{sh_dq_exit_opt_state, separator, sh_separator_state},
	{sh_dq_exit_opt_state, exit_state, sh_exit_state},

	{sh_dq_exit_arg_state, padding, sh_arg_pad_state},
	{sh_dq_exit_arg_state, error, sh_error_state},
	{sh_dq_exit_arg_state, dq, sh_dq_arg_state},
	{sh_dq_exit_arg_state, sq, sh_sq_arg_state},
	{sh_dq_exit_arg_state, backslash, sh_bs_arg_state},
	{sh_dq_exit_arg_state, cmd, sh_arg_state},
	{sh_dq_exit_arg_state, opt, sh_arg_state},
	{sh_dq_exit_arg_state, arg, sh_arg_state},
	{sh_dq_exit_arg_state, separator, sh_separator_state},
	{sh_dq_exit_arg_state, exit_state, sh_exit_state},

	{sh_sq_cmd_state, padding, sh_sq_cmd_state},
	{sh_sq_cmd_state, error, sh_error_state},
	{sh_sq_cmd_state, dq, sh_sq_cmd_state},
	{sh_sq_cmd_state, sq, sh_sq_exit_cmd_state},
	{sh_sq_cmd_state, backslash, sh_sq_cmd_state},
	{sh_sq_cmd_state, cmd, sh_sq_cmd_state},
	{sh_sq_cmd_state, opt, sh_sq_cmd_state},
	{sh_sq_cmd_state, arg, sh_sq_cmd_state},
	{sh_sq_cmd_state, separator, sh_sq_cmd_state},
	{sh_sq_cmd_state, exit_state, sh_exit_state},

	{sh_sq_opt_state, padding, sh_sq_opt_state},
	{sh_sq_opt_state, error, sh_error_state},
	{sh_sq_opt_state, dq, sh_sq_opt_state},
	{sh_sq_opt_state, sq, sh_sq_exit_opt_state},
	{sh_sq_opt_state, backslash, sh_sq_opt_state},
	{sh_sq_opt_state, cmd, sh_sq_opt_state},
	{sh_sq_opt_state, opt, sh_sq_opt_state},
	{sh_sq_opt_state, arg, sh_sq_opt_state},
	{sh_sq_opt_state, separator, sh_sq_opt_state},
	{sh_sq_opt_state, exit_state, sh_exit_state},

	{sh_sq_arg_state, padding, sh_sq_arg_state},
	{sh_sq_arg_state, error, sh_error_state},
	{sh_sq_arg_state, dq, sh_sq_arg_state},
	{sh_sq_arg_state, sq, sh_sq_exit_arg_state},
	{sh_sq_arg_state, backslash, sh_sq_arg_state},
	{sh_sq_arg_state, cmd, sh_sq_arg_state},
	{sh_sq_arg_state, opt, sh_sq_arg_state},
	{sh_sq_arg_state, arg, sh_sq_arg_state},
	{sh_sq_arg_state, separator, sh_sq_arg_state},
	{sh_sq_arg_state, exit_state, sh_exit_state},

	{sh_sq_exit_cmd_state, padding, sh_cmd_pad_state},
	{sh_sq_exit_cmd_state, error, sh_error_state},
	{sh_sq_exit_cmd_state, dq, sh_dq_cmd_state},
	{sh_sq_exit_cmd_state, sq, sh_sq_cmd_state},
	{sh_sq_exit_cmd_state, backslash, sh_bs_cmd_state},
	{sh_sq_exit_cmd_state, cmd, sh_cmd_state},
	{sh_sq_exit_cmd_state, opt, sh_cmd_state},
	{sh_sq_exit_cmd_state, arg, sh_cmd_state},
	{sh_sq_exit_cmd_state, separator, sh_separator_state},
	{sh_sq_exit_cmd_state, exit_state, sh_exit_state},

	{sh_sq_exit_opt_state, padding, sh_opt_pad_state},
	{sh_sq_exit_opt_state, error, sh_error_state},
	{sh_sq_exit_opt_state, dq, sh_dq_opt_state},
	{sh_sq_exit_opt_state, sq, sh_sq_opt_state},
	{sh_sq_exit_opt_state, backslash, sh_bs_opt_state}, 
	{sh_sq_exit_opt_state, cmd, sh_opt_state},
	{sh_sq_exit_opt_state, opt, sh_opt_state},
	{sh_sq_exit_opt_state, arg, sh_opt_state},
	{sh_sq_exit_opt_state, separator, sh_separator_state},
	{sh_sq_exit_opt_state, exit_state, sh_exit_state},

	{sh_sq_exit_arg_state, padding, sh_arg_pad_state},
	{sh_sq_exit_arg_state, error, sh_error_state},
	{sh_sq_exit_arg_state, dq, sh_dq_arg_state},
	{sh_sq_exit_arg_state, sq, sh_sq_arg_state},
	{sh_sq_exit_arg_state, backslash, sh_bs_arg_state},
	{sh_sq_exit_arg_state, cmd, sh_arg_state},
	{sh_sq_exit_arg_state, opt, sh_arg_state},
	{sh_sq_exit_arg_state, arg, sh_arg_state},
	{sh_sq_exit_arg_state, separator, sh_separator_state},
	{sh_sq_exit_arg_state, exit_state, sh_exit_state},

	{sh_bs_cmd_state, padding, sh_cmd_pad_state},
	{sh_bs_cmd_state, error, sh_error_state},
	{sh_bs_cmd_state, dq, sh_dq_cmd_state},
	{sh_bs_cmd_state, sq, sh_sq_cmd_state},
	{sh_bs_cmd_state, backslash, sh_bs_cmd_state},
	{sh_bs_cmd_state, cmd, sh_cmd_state},
	{sh_bs_cmd_state, opt, sh_cmd_state},
	{sh_bs_cmd_state, arg, sh_cmd_state},
	{sh_bs_cmd_state, separator, sh_separator_state},
	{sh_bs_cmd_state, exit_state, sh_exit_state},

	{sh_bs_opt_state, padding, sh_opt_pad_state},
	{sh_bs_opt_state, error, sh_error_state},
	{sh_bs_opt_state, dq, sh_dq_opt_state},
	{sh_bs_opt_state, sq, sh_sq_opt_state},
	{sh_bs_opt_state, backslash, sh_bs_opt_state},
	{sh_bs_opt_state, cmd, sh_opt_state},
	{sh_bs_opt_state, opt, sh_opt_state},
	{sh_bs_opt_state, arg, sh_opt_state},
	{sh_bs_opt_state, separator, sh_separator_state},
	{sh_bs_opt_state, exit_state, sh_exit_state},

	{sh_bs_arg_state, padding, sh_arg_pad_state},
	{sh_bs_arg_state, error, sh_error_state},
	{sh_bs_arg_state, dq, sh_dq_arg_state},
	{sh_bs_arg_state, sq, sh_sq_arg_state},
	{sh_bs_arg_state, backslash, sh_bs_arg_state},
	{sh_bs_arg_state, cmd, sh_arg_state},
	{sh_bs_arg_state, opt, sh_arg_state},
	{sh_bs_arg_state, arg, sh_arg_state},
	{sh_bs_arg_state, separator, sh_separator_state},
	{sh_bs_arg_state, exit_state, sh_exit_state},

	{sh_error_state, padding, sh_error_state},
	{sh_error_state, error, sh_error_state},
	{sh_error_state, dq, sh_error_state},
	{sh_error_state, sq, sh_error_state},
	{sh_error_state, backslash, sh_error_state},
	{sh_error_state, cmd, sh_error_state},
	{sh_error_state, opt, sh_error_state},
	{sh_error_state, arg, sh_error_state},
	{sh_error_state, separator, sh_error_state},
	{sh_error_state, exit_state, sh_exit_state},

	{sh_exit_state, padding, sh_exit_state},
	{sh_exit_state, error, sh_exit_state},
	{sh_exit_state, dq, sh_exit_state},
	{sh_exit_state, sq, sh_exit_state},
	{sh_exit_state, backslash, sh_exit_state},
	{sh_exit_state, cmd, sh_exit_state},
	{sh_exit_state, opt, sh_exit_state},
	{sh_exit_state, arg, sh_exit_state},
	{sh_exit_state, separator, sh_exit_state},
	{sh_exit_state, exit_state, sh_exit_state}
};

#endif
