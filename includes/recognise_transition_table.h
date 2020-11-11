/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   recognise_transition_table.h                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/20 12:26:08 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/11 15:02:17 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RECOGNISE_TRANSITION_TABLE_H
# define RECOGNISE_TRANSITION_TABLE_H

# define RECOG_TABLE_SIZE 21

static t_recognition_obj const	g_tokenrecog_table[] =
{
	{"echo", cmd},
	{"cd", cmd},
	{"pwd", cmd},
	{"export", cmd},
	{"unset", cmd},
	{"env", cmd},
	{"exit", cmd},
	{">>", separator},
	{"&&", separator},
	{"<", separator},
	{">", separator},
	{"|", separator},
	{";", separator},
	{"$?", arg},
	{"$", arg},
	{"\\", backslash},
	{"\"", dq},
	{"\'", sq},
	{"-", opt},
	{" ", padding},
	{"	", padding}
};

#endif
