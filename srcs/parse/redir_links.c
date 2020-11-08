/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_links.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/08 19:42:11 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/08 21:08:54 by limartin      ########   odam.nl         */
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
		if (head->left != NULL) //this might work differently for redir blocks compared to comp block, head will probably be malloc'd
			free(head);
		head = NULL;
		head = tmp;
	}
}
