/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 11:18:20 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/26 11:48:48 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h" //TODO: How to include this

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



void					print_components(t_icomp *icur);
void					free_components(t_icomp *head);


/*
** Execute
*/

void					execute(t_vector *env, t_icomp cmd);


t_vector		*convert_env(char **envp);



#endif
