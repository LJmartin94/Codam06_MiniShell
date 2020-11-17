/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 11:18:20 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/17 15:30:38 by jsaariko      ########   odam.nl         */
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

typedef struct			s_redir
{
	char				*type;
	char				*file;
	struct s_redir		*left;
	struct s_redir		*right;
}						t_redir;

typedef struct			s_icomp
{
	char				*sep;
	char				*cmd;
	char				*opt;
	char				*arg;
	int					id;
	struct t_redir		*rdhead;
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

/*
** //TODO: Debug-only prototypes! Remove when no longer used.
*/

void					print_components(t_icomp *icur);

#endif
