/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fsm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 12:37:14 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/15 20:06:19 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FSM_H
# define FSM_H

typedef enum	s_transition_code
{
	state_padding,
	state_command,
	state_error
}				t_transition_code;

t_transition_code	sh_entry_state(t_token *this, t_icomp *icur);
t_transition_code	sh_command_state(t_token *this, t_icomp *icur);
t_transition_code	sh_error_state(t_token *this, t_icomp *icur);

typedef struct	s_transition_obj
{
	t_transition_code	(*orig_state)(t_token *this, t_icomp *icur);
	t_transition_code	transition_code;
	t_transition_code	(*next_state)(t_token *this, t_icomp *icur);
}				t_transition_obj;

#endif