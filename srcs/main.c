/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/20 14:07:40 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"
#include "execute.h"
#include <signal.h>

static void	parse_and_execute(t_vector *env, char **str, t_icomp *comp)
{
	int		no_error;

	no_error = 1;
	expand_env(env, str);
	parse_input(*str, comp);
	no_error = no_syntax_errors(comp);
	if (no_error)
		execute(env, comp);
	free_components(comp);
}

void		run_shell(t_vector *env, char *buf)
{
	char	**split;
	t_icomp	comp_blocks;
	size_t	i = 0;
	int		no_error;
	t_icomp error;

	split = split_unless_quote(buf, ';');
	no_error = 1;
	parse_input(buf, &error);
	no_error = no_syntax_errors(&error);
	while (split[i] != NULL && no_error)
	{
		parse_and_execute(env, &(split[i]), &comp_blocks);
		i++;
	}
	free_matrix(split);
}

int			get_input(t_vector *env)
{
	char	*buf;
	int		ret;

	e_write(STDOUT_FILENO, "\U0001F40C ", 6);
	ret = get_next_line(STDIN_FILENO, &buf);
	if (ret == 0)
	{
		e_write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	if (ret < 0)
		error_exit_msg(C_GNL_FAIL, E_GNL_FAIL);
	run_shell(env, buf);
	free(buf);
	return (ret);
}

/*
**  //TODO: move
*/

int		g_ret_val;
int		g_amt_processes;
char	*g_pwd;

int			main(int ac, char **av, char **envp)
{
	t_vector	*env;

	g_pwd = getcwd(g_pwd, 0);
	if (g_pwd == NULL)
		error_exit_msg(1, "Invalid location in file structure\n");
	g_ret_val = 0;
	g_amt_processes = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	env = init_env(envp);
	(void)ac;
	(void)av;
	while (1)
		get_input(env);
	return (0);
}
