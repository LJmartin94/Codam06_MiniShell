/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_table.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/16 12:31:08 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/20 12:26:35 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_TABLE_H
# define TOKEN_TABLE_H

typedef struct	s_special_token
{
	char	*token;
	int		len;
}				t_special_token;

#define token_table_size 11

static t_special_token const g_token_table[] =
{
	{"$?", 2},
	{">>", 2},
	{"&&", 2},
	{"<", 1},
	{">", 1},
	{"|", 1},
	{"\"", 1},
	{"\'", 1},
	{"$", 1},
	{";", 1},
	{"\\", 1}
};

#endif
