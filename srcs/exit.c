/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 12:34:47 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/27 12:36:44 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int ft_exit(t_vector *env, t_icomp cmd)
{
	(void)env;
	(void)cmd;
	exit(0); //TODO: Make sure to run through all pid's and exit those as well?
}