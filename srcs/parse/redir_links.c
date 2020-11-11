/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_links.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/08 19:42:11 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/11 16:29:35 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "error.h"

int		ft_redirconst(t_redir *tonull)
{
	tonull->type = ft_strdup("");
	tonull->file = ft_strdup("");
	if (tonull->type == NULL || tonull->file == NULL)
		error_exit_errno();
	tonull->left = NULL;
	tonull->right = NULL;
	return (0);
}

void	ft_add_redir(t_redir **head, t_redir *this)
{
	t_redir *cur;
	t_redir	*left;

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
** //TODO:
** Below function is still a work in progress,
** particularly "if (head->left != NULL)"
** will probably work differently as even the first link
** will be malloc'd (unlike first comp block)
*/

void	free_redirs(t_redir *head)
{
	t_redir *tmp;

	while (head)
	{
		tmp = head->right;
		if (head->type != NULL)
			free(head->type);
		head->type = NULL;
		if (head->file != NULL)
			free(head->file);
		head->file = NULL;
		if (head->left != NULL)
			free(head);
		head = NULL;
		head = tmp;
	}
}
