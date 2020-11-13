/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arg_links.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 19:20:22 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/13 09:28:01 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "error.h"

// typedef struct			s_arg
// {
// 	int					id;
// 	char				*type;
// 	char				*value;
// 	char				*pad;
// 	struct s_redir		*left;
// 	struct s_redir		*right;
// }						t_arg;

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
		if (head->left != NULL)
			free(head);
		head = NULL;
		head = tmp;
	}
}
