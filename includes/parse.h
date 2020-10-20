/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 14:04:54 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/20 11:44:32 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>

/*
** Tokeniser structs & functions
*/

typedef struct	s_token
{
	char				*token;
	struct s_token		*next;
}				t_token;

t_token					*get_tokens(const char *input);
void					add_token(t_token **head, t_token *token);
t_token					*create_token(char *tokens, int j, size_t len);
void					free_matrix(char **tokens);
void					parse_input(const char *input);
void					manage_fsm(t_token *tokens);

/*
** Composition-block structs & functions
*/

typedef enum	s_comp_type
{
	type_command,
	type_option,
	type_arg,
	type_separator
}				t_comp_type;

typedef struct	s_icomp
{
	char				*sep;
	char				*cmd;
	char				*opt;
	char				*arg;
	struct s_icomp		*next;
}				t_icomp;

int						ft_compconst(t_icomp *tonull);

/*
** FSM structs & functions
*/

typedef enum	s_transition_code
{
	state_entry,
	state_padding,
	state_error,
	state_command,
	state_option,
	state_arg,
	state_separator
}				t_transition_code;

t_transition_code		sh_entry_state(t_token *this, t_icomp *icur);
t_transition_code		sh_error_state(t_token *this, t_icomp *icur);
t_transition_code		sh_command_state(t_token *this, t_icomp *icur);
t_transition_code		sh_option_state(t_token *this, t_icomp *icur);
t_transition_code		sh_argument_state(t_token *this, t_icomp *icur);
t_transition_code		sh_separator_state(t_token *this, t_icomp *icur);

typedef struct	s_transition_obj
{
	t_transition_code	(*orig_state)(t_token *this, t_icomp *icur);
	t_transition_code	transition_code;
	t_transition_code	(*next_state)(t_token *this, t_icomp *icur);
}				t_transition_obj;

/* 
** General parsing structs & functions
*/

void					xt_quit_in_parse(int ret);

#endif