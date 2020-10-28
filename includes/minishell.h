/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 11:18:20 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/28 15:05:46 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** //TODO: Debug-only includes! Remove when no longer used.
*/

# include <stdio.h>

/*
** Structure for parsed commands
*/

typedef struct			s_icomp
{
	char				*sep;
	char				*cmd;
	char				*opt;
	char				*arg;
	int					id;
	struct s_icomp		*left;
	struct s_icomp		*right;
}						t_icomp;

/*
** Function that calls parser
*/

void					parse_input(const char *input, t_icomp *comp_blocks);

/*
** Function that runs shell
*/


void					execute(t_icomp *comp);


/*
** Function that frees all component blocks after use
*/

void					free_components(t_icomp *head);

/*
** //TODO: Debug-only prototypes! Remove when no longer used.
*/

void					print_components(t_icomp *icur);

#endif
