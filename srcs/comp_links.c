/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   comp_links.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/19 18:03:33 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/23 12:34:21 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "error.h"

int		ft_compconst(t_icomp *tonull)
{
	tonull->sep = NULL;
	tonull->cmd = NULL;
	tonull->opt = NULL;
	tonull->arg = NULL;
	tonull->id = 0;
	tonull->right = NULL;
	tonull->left = NULL;
	return (0);
}

void	ft_add_component(t_icomp **head, t_icomp *this)
{
	t_icomp *cur;
	t_icomp	*left;

	if (*head == NULL)
	{
		*head = this;
		return ;
	}
	cur = *head;
	left = cur;
	while (cur->right != NULL)
		cur = cur->right;
	cur->right = this;
	this->left = left;
}

/*
** Below function writes the token's string value 'token->token' to a given
** field of the current component, appending if a value exists or creating
** one if it does not exist yet.
*/

int		ft_add_token_to_comp(t_token *token, char **field)
{
	if (*field == NULL)
		*field = ft_strdup(token->token);
	else
		*field = ft_strjoin(*field, token->token);
	if (*field == NULL)
		error_exit_errno();
	return (0);
}

void	free_components(t_icomp *head)
{
	t_icomp *tmp;

	while (head->right)
	{
		tmp = head->right;
		if (head->sep != NULL)
			free(head->sep);
		if (head->cmd != NULL)
			free(head->cmd);
		if (head->opt != NULL)
			free(head->opt);
		if (head->arg != NULL)
			free(head->arg);
		// if (head->left != NULL)
		// 	free(head);
		head = tmp;
	}
}
