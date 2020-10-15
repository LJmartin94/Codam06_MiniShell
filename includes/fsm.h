/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fsm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 12:37:14 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/15 17:30:57 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FSM_H
# define FSM_H

t_transition_code	entry_state(t_token *this, t_icomp *icur);
t_transition_code	command_state(t_token *this, t_icomp *icur);
t_transition_code	error_state(t_token *this, t_icomp *icur);

typedef enum	s_transition_code
{
	padding,
	command,
	error
}				t_transition_code;

typedef struct	s_transition_obj
{
	t_transition_code	(*orig_state)(const char *);
	t_transition_code	transition_code;
	t_transition_code	(*next_state)(const char *);
}				t_transition_obj;

t_transition_obj const g_transition_table[] =
{
	{entry_state, padding, entry_state},
	{entry_state, command, command_state},
	{entry_state, error, error_state}
};

#endif