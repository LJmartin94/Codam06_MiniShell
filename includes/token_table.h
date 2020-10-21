/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_table.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/16 12:31:08 by jsaariko      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/10/21 15:45:51 by limartin      ########   odam.nl         */
=======
/*   Updated: 2020/10/19 15:51:23 by jsaariko      ########   odam.nl         */
>>>>>>> master
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

<<<<<<< HEAD
# define TOKEN_TABLE_SIZE 11

=======
>>>>>>> master
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
