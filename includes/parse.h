/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 14:04:54 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/08 21:13:55 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include "minishell.h"

/*
** Tokeniser structs & functions
*/

typedef struct			s_token
{
	char				*token;
	struct s_token		*next;
}						t_token;

t_token					*get_tokens(const char *input);
void					add_token(t_token **head, t_token *token);
t_token					*create_token(const char *tokens, int j, size_t len);
void					free_tokens(t_token *head);

/*
** Composition-block functions
*/

int						ft_compconst(t_icomp *tonull);
void					ft_add_component(t_icomp **head, t_icomp *this);
int						ft_add_token_to_comp(t_token *token, char **field);

/*
** Redirection-block functions
*/

int						ft_redirconst(t_redir *tonull);
void					ft_add_redir(t_redir **head, t_redir *this);

/*
** FSM structs & functions
*/

typedef	enum			e_transition_code
{
	padding,
	error,
	cmd,
	opt,
	arg,
	separator,
	backslash,
	dq,
	sq,
	exit_state
}						t_transition_code;

void					manage_fsm(t_token *tokens, t_icomp *head);

t_transition_code		sh_entry_state(t_token **this, t_icomp **icur);
t_transition_code		sh_error_state(t_token **this, t_icomp **icur);
t_transition_code		sh_exit_state(t_token **this, t_icomp **icur);

t_transition_code		sh_cmd_state(t_token **this, t_icomp **icur);
t_transition_code		sh_opt_state(t_token **this, t_icomp **icur);
t_transition_code		sh_arg_state(t_token **this, t_icomp **icur);
t_transition_code		sh_separator_state(t_token **this, t_icomp **icur);

t_transition_code		sh_cmd_pad_state(t_token **this, t_icomp **icur);
t_transition_code		sh_opt_pad_state(t_token **this, t_icomp **icur);
t_transition_code		sh_arg_pad_state(t_token **this, t_icomp **icur);

t_transition_code		sh_dq_cmd_state(t_token **this, t_icomp **icur);
t_transition_code		sh_dq_opt_state(t_token **this, t_icomp **icur);
t_transition_code		sh_dq_arg_state(t_token **this, t_icomp **icur);

t_transition_code		sh_dq_bs_cmd_state(t_token **this, t_icomp **icur);
t_transition_code		sh_dq_bs_opt_state(t_token **this, t_icomp **icur);
t_transition_code		sh_dq_bs_arg_state(t_token **this, t_icomp **icur);

t_transition_code		sh_dq_exit_cmd_state(t_token **this, t_icomp **icur);
t_transition_code		sh_dq_exit_opt_state(t_token **this, t_icomp **icur);
t_transition_code		sh_dq_exit_arg_state(t_token **this, t_icomp **icur);

t_transition_code		sh_sq_cmd_state(t_token **this, t_icomp **icur);
t_transition_code		sh_sq_opt_state(t_token **this, t_icomp **icur);
t_transition_code		sh_sq_arg_state(t_token **this, t_icomp **icur);

t_transition_code		sh_sq_exit_cmd_state(t_token **this, t_icomp **icur);
t_transition_code		sh_sq_exit_opt_state(t_token **this, t_icomp **icur);
t_transition_code		sh_sq_exit_arg_state(t_token **this, t_icomp **icur);

t_transition_code		sh_bs_cmd_state(t_token **this, t_icomp **icur);
t_transition_code		sh_bs_opt_state(t_token **this, t_icomp **icur);
t_transition_code		sh_bs_arg_state(t_token **this, t_icomp **icur);

t_transition_code		recognise_token_state(t_token *this);

int						validate_option_flags(t_icomp **icur);

typedef struct			s_recognition_obj
{
	char				*to_compare;
	t_transition_code	ret;
}						t_recognition_obj;

typedef struct			s_flag_validation_obj
{
	char				*cmd;
	char				*flag;
}						t_flag_validation_obj;

typedef struct			s_transition_obj
{
	t_transition_code	(*orig_state)(t_token **this, t_icomp **icur);
	t_transition_code	transition_code;
	t_transition_code	(*next_state)(t_token **this, t_icomp **icur);
}						t_transition_obj;

/*
** General parsing structs & functions
*/

void					xt_quit_in_parse(int ret);

/*
** //TODO: Debug-only prototypes! Remove when no longer used.
*/

void					print_tokens(t_token *tokens);

#endif
