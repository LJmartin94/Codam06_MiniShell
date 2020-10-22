/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_table.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/24 13:03:45 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_TABLE_H
# define TOKEN_TABLE_H

# define TOKEN_TABLE_SIZE 11

typedef struct	s_special_token
{
	char		*token;
	int			len;
}				t_special_token;

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
