/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 13:49:26 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/20 15:23:03 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "libft.h"

int		escape_being_lost(t_vector *env, char *path);
void	update_pwd(t_vector *env);
void	cd_error(char *path);

#endif
