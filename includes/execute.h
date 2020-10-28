/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 13:40:30 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/28 15:14:25 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

/*
** // TODO: Needed:
** global return
** global pwd (works even when unset)
** global list of pid
*/

typedef struct	s_env
{
	char *key;
	char *value;
}				t_env;

int				ft_echo(t_icomp *cmd);
void			invalid_cmd(t_icomp *cmd);


#endif
