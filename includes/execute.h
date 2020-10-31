/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 13:40:30 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/31 12:43:57 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include <libc.h>

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

typedef	int		(*t_cmd)(t_vector *, t_icomp *);

int				ft_echo(t_vector *env, t_icomp *cmd);
int				ft_env(t_vector *env, t_icomp *cmd);
int				ft_export(t_vector *env, t_icomp *cmd);
int				ft_unset(t_vector *env, t_icomp *cmd);
int				ft_pwd(t_vector *env, t_icomp *cmd);

int				compare_key(t_env *data, char *item);

t_env			*get_env_item(char *env_str);
void			free_env_item(t_env *item);
void			free_env(t_vector *env);
void			free_envp(char **envp);

void			invalid_cmd(t_icomp *cmd);

#endif
