/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   statetable.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 19:53:22 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/15 20:08:02 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATETABLE_H
# define STATETABLE_H

t_transition_obj const g_shellstate_table[] =
{
	{sh_entry_state, state_padding, sh_entry_state},
	{sh_entry_state, state_command, sh_command_state},
	{sh_entry_state, state_error, sh_error_state}
};

#endif