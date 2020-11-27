/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_control_states.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/27 15:02:47 by lindsay       #+#    #+#                 */
/*   Updated: 2020/11/27 17:03:02 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_transition_code	sh_rd_entry_state(t_token **this, t_icomp **icur)
{
	t_transition_code	id;
	t_redir				*last;
	t_redir				*new;

	if (ft_strlen(((*icur)->rdhead)->file) > 0)
	{
		new = (t_redir *)e_malloc(sizeof(t_redir));
		ft_redirconst(new);
		ft_add_redir(&(*icur)->rdhead, new);
	}
	last = (*icur)->rdhead;
	while (last->right != NULL)
		last = last->right;
	id = recognise_token_state(*this);
	if (id == redir_out || id == dredir_out)
		ft_add_token_to_comp((*this), &((last)->type_out));
	if (id == redir_in)
		ft_add_token_to_comp((*this), &((last)->type_in));
	*this = (*this)->next;
	id = exit_state;
	if ((*this) != NULL)
		id = recognise_token_state(*this);
	if (id == redir_out && ft_strlen(last->type_out) != 0)
		id = error;
	return (id);
}
