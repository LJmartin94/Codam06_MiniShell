/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   comp_links.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/19 18:03:33 by limartin      #+#    #+#                 */
/*   Updated: 2021/01/06 11:43:11 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "error.h"

int		ft_compconst(t_icomp *tonull)
{
	tonull->sep = ft_strdup("");
	tonull->cmd = ft_strdup("");
	tonull->opt = ft_strdup("");
	if (tonull->sep == NULL || tonull->cmd == NULL || \
	tonull->opt == NULL)
		error_exit_errno();
	tonull->arg = (t_arg *)e_malloc(sizeof(t_arg));
	ft_argconst(tonull->arg);
	tonull->id = 0;
	tonull->rdhead = (t_redir *)e_malloc(sizeof(t_redir));
	ft_redirconst(tonull->rdhead);
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
	char *new_val;

	new_val = ft_strjoin(*field, token->token);
	if (new_val == NULL)
		error_exit_errno();
	free(*field);
	*field = new_val;
	return (0);
}

void	free_components(t_icomp *head)
{
	t_icomp *tmp;

	while (head)
	{
		tmp = head->right;
		if (head->sep != NULL)
			free(head->sep);
		head->sep = NULL;
		if (head->cmd != NULL)
			free(head->cmd);
		head->cmd = NULL;
		if (head->opt != NULL)
			free(head->opt);
		head->opt = NULL;
		if (head->arg != NULL)
			free_args(head->arg);
		head->arg = NULL;
		if (head->rdhead != NULL)
			free_redirs(head->rdhead);
		head->arg = NULL;
		if (head->left != NULL)
			free(head);
		head = NULL;
		head = tmp;
	}
}
