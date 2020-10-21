/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   recognise_transition_table.h                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/20 12:26:08 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/21 15:36:18 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RECOGNISE_TRANSITION_TABLE_H
# define RECOGNISE_TRANSITION_TABLE_H

# define RECOG_TABLE_SIZE 19

static t_recognition_obj const	g_tokenrecog_table[] =
{
	{"echo", command},
	{"cd", command},
	{"pwd", command},
	{"export", command},
	{"unset", command},
	{"env", command},
	{"exit", command},
	{"$?", separator},
	{">>", separator},
	{"&&", separator},
	{"<", separator},
	{">", separator},
	{"|", separator},
	{"\"", separator},
	{"\'", separator},
	{"$", separator},
	{";", separator},
	{"\\", separator},
	{"-n", option}
};

#endif
