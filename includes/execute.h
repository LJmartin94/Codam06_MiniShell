/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 13:40:30 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/05 14:22:34 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include <unistd.h>
# include <sys/wait.h>

/*
** Store env
*/

typedef struct	s_env
{
	char *key;
	char *value;
}				t_env;

/*
** Amount of current running processes
*/

extern int g_amt_processes;

/*
** Global return value
*/

extern int g_ret_val;

/*
** Builtin prototypes
*/

typedef	int		(*t_cmd)(t_vector *, t_icomp *, int);

int				ft_echo(t_vector *env, t_icomp *cmd, int fd);
int				ft_exit(t_vector *env, t_icomp *cmd, int fd);
int				ft_pwd(t_vector *env, t_icomp *cmd, int fd);
int				ft_cd(t_vector *env, t_icomp *cmd, int fd);
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
int				validate_env_key(const char *arg);

/*
** Execute
*/

t_cmd			get_command(t_icomp *comp);
void			exec_command(t_vector *env, t_icomp *cmd,
					t_vector *fd_list, t_vector *pid_list);

void			handle_redirections(t_icomp *comp, int p_fd[2],
					t_vector *fd_list);
int				redirect_builtin(t_icomp *comp);

char			*find_path(t_vector *env, t_icomp *comp);
char			**build_argv(t_icomp *comp);

void			expand_env_arg(t_vector *env, t_icomp *comp);
void			expand_env(t_vector *env, char **str);

/*
** //TODO: Error handling (change this)?
*/

void			invalid_cmd(t_icomp *cmd);
void			cmd_error(t_icomp *cmd, char *msg);
int				no_syntax_errors(t_icomp *head);

/*
** Execute utils, mainly for testing purposes
** //TODO: Remove unnecessary ones
*/

typedef struct	s_quotes
{
	int quote;
	int dquote;
}				t_quotes;

int				cmp_pid(int *pid1, int *pid2);
void			free_matrix(char **matrix);

#endif
