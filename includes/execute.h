/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 13:40:30 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/11 15:19:55 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

/*
** Store env
*/

typedef struct	s_env
{
	char *key;
	char *value;
}				t_env;

/*
** Store pid
*/

t_vector g_pid_list;

typedef struct	s_process
{
	int	fd;
	int pid;
}				t_process;

/*
** Store return value
*/

int g_ret_val;

/*
** Builtin prototypes
*/

typedef	int		(*t_cmd)(t_vector *, t_icomp *, int);

int				ft_echo(t_vector *env, t_icomp *cmd, int fd);
int				ft_exit(t_vector *env, t_icomp *cmd, int fd);
int				ft_env(t_vector *env, t_icomp *cmd, int fd);
int				ft_export(t_vector *env, t_icomp *cmd, int fd);
int				ft_unset(t_vector *env, t_icomp *cmd, int fd);

/*
** Env utils
*/

int				compare_key(t_env *data, char *item);
t_env			*get_env_item(char *env_str);
void			free_env_item(t_env *item);
void			free_env(t_vector *env);
void			free_envp(char **envp);

/*
** Execute
*/

t_cmd			get_command(t_icomp *comp);
int				exec_command(t_vector *env, t_icomp *cmd, int stdin);

void			handle_redirections(t_icomp *comp, int p_fd[2], int stdin);
char			*find_path(t_vector *env, t_icomp *comp);
char			**build_argv(t_icomp *comp);

/*
** //TODO: Error handling (change this)?
*/

void			invalid_cmd(t_icomp *cmd);
void			cmd_error(t_icomp *cmd, char *msg, int fd);

/*
** Execute utils, mainly for testing purposes
** //TODO: Remove unnecessary ones
*/

int				pid_print(int fd, t_process *pid);
int				cmp_pid(int *pid1, int *pid2);
void			free_matrix(char **matrix);

#endif
