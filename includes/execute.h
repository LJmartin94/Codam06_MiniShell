/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 13:40:30 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/24 13:45:21 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "vector.h"

typedef struct	s_env
{
	char *key;
	char *value;
}				t_env;

t_vector		*convert_env(char **envp);
int				ft_env(t_vector *env);
int				ft_export(t_vector *env, char *cmd);
int				ft_unset(t_vector *env, char *cmd);

#endif
