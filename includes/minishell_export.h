/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_export.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 18:09:49 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/07 18:11:37 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXPORT_H
# define MINISHELL_EXPORT_H

# include "execute.h"

char	*export_join_args(t_arg **arg);
int		env_no_params(t_vector *env, int fd);
void	edit_env(t_vector *env, t_env *item, int pos);

#endif