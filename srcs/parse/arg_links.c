/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arg_links.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 19:20:22 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/12 19:43:50 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
