/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arg_links.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 19:20:22 by limartin      #+#    #+#                 */
/*   Updated: 2021/01/06 11:50:18 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "error.h"

int		ft_argconst(t_arg *tonull)
{
	tonull->id = 0;
	tonull->type = ft_strdup("");
	tonull->value = ft_strdup("");
	tonull->pad = ft_strdup("");
	if (tonull->type == NULL || tonull->value == NULL \
	|| tonull->pad == NULL)
		error_exit_errno();
	tonull->left = NULL;
	tonull->right = NULL;
	return (0);
}

void	ft_add_arg(t_arg **head, t_arg *this)
{
	t_arg	*cur;
	t_arg	*left;
	int		id;

	if (*head == NULL)
	{
		*head = this;
		return ;
	}
	cur = *head;
	left = cur;
	id = 1;
	while (cur->right != NULL)
	{
		cur = cur->right;
		id++;
	}
	this->id = id;
	cur->right = this;
	this->left = left;
}

void	free_args(t_arg *head)
{
	t_arg *tmp;

	while (head)
	{
		tmp = head->right;
		if (head->type != NULL)
			free(head->type);
		head->type = NULL;
		if (head->value != NULL)
			free(head->value);
		head->value = NULL;
		if (head->pad != NULL)
			free(head->pad);
		head->pad = NULL;
		free(head);
		head = NULL;
		head = tmp;
	}
}
