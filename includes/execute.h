/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 13:40:30 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/28 17:30:23 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

/*
** TODO: Needed:
** global return
** global pwd (works even when unset)
** global list of pid
*/

typedef struct	s_env
{
	char *key;
	char *value;
}				t_env;

typedef	int		(*t_cmd)(t_icomp *);

int				ft_env(t_vector *env, t_icomp cmd);
int				ft_export(t_vector *env, t_icomp cmd);
int				ft_unset(t_vector *env, t_icomp cmd);
int				ft_echo(t_vector *env, t_icomp cmd);
t_env			*get_env_item(char *env_str);
void			invalid_cmd(t_icomp cmd);

#endif
