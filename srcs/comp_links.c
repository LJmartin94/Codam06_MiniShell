/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   comp_links.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/19 18:03:33 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/19 18:52:23 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int		ft_compconst(t_icomp *tonull)
{
	tonull->sep = NULL;
	tonull->cmd = NULL;
	tonull->opt = NULL;
	tonull->arg = NULL;
	tonull->next = NULL;
	return (0);
}
