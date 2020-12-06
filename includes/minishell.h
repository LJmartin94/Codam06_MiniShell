/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 11:18:20 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/06 11:44:32 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

/*
** //TODO: Debug-only includes! Remove when no longer used.
*/

# include <stdio.h>

/*
** Structure for parsed commands
*/

typedef struct			s_arg
{
	int					id;
	char				*type;
	char				*value;
	char				*pad;
	struct s_arg		*left;
	struct s_arg		*right;
}						t_arg;

typedef struct			s_redir
{
	char				*type_in;
	char				*type_out;
	char				*file;
	struct s_redir		*left;
	struct s_redir		*right;
}						t_redir;

typedef struct			s_icomp
{
	int					id;
	char				*sep;
	char				*cmd;
	char				*opt;
	t_arg				*arg;
	t_redir				*rdhead;
	struct s_icomp		*left;
	struct s_icomp		*right;
}						t_icomp;

/*
** Function that calls parser
*/

void					parse_input(const char *input, t_icomp *comp_blocks);

/*
** Utils
*/

t_vector				*envp_to_env(char **envp);
char					**env_to_envp(t_vector *envp);
char					**split_unless_quote(char const *s, char c);

/*
** Execute
*/

void					execute(t_vector *env, t_icomp *comp);

/*
** Signal handlers
*/

void					handle_sigint(int signo);
void					handle_sigquit(int signo);

/*
** Function that frees all component blocks after use
*/

void					free_components(t_icomp *head);
void					free_redirs(t_redir *head);
void					free_args(t_arg *head);

/*
** //TODO: Debug-only prototypes! Remove when no longer used.
*/

void					print_components(t_icomp *icur);

#endif
