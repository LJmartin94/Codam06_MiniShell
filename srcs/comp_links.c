/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   comp_links.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/19 18:03:33 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/20 17:50:30 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"

int		ft_compconst(t_icomp *tonull)
{
	tonull->sep = NULL;
	tonull->cmd = NULL;
	tonull->opt = NULL;
	tonull->arg = NULL;
	tonull->next = NULL;
	return (0);
}

void	ft_add_component(t_icomp **head, t_icomp *this)
{
	t_icomp *cur;

	if (*head == NULL)
	{
		*head = this;
		return ;
	}
	cur = *head;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = this;
}

/*
** Below function writes the token's string value 'token->token' to a given
** field of the current component, appending if a value exists or creating
** one if it does not exist yet.
*/

int		ft_add_token_to_comp(t_token *token, char **field) //need to still check for malloc fails in strdup etc
{
	if (*field == NULL)
		*field = ft_strdup(token->token);
	else
		*field = ft_strjoin(*field, token->token);
	if (*field == NULL)
		xt_quit_in_parse(-1);
	return (0);
}
