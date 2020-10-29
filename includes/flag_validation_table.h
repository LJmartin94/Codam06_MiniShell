/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flag_validation_table.h                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/20 12:26:08 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/28 20:25:02 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAG_VALIDATION_TABLE_H
# define FLAG_VALIDATION_TABLE_H

# define FLAG_TABLE_SIZE 2

static t_flag_validation_obj const	g_flagvalid_table[] =
{
	{"echo", "n"},
	{"echo", "newline"},
};

#endif
