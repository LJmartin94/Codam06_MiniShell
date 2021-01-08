/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/08 16:28:13 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"
#include "execute.h"
#include <signal.h>

static int	parse_and_execute(t_vector *env, char **str, t_icomp *comp, \
int exec)
{
	int		no_error;

	no_error = 1;
	expand_env(env, str);
	parse_input(*str, comp);
	if (exec)
		execute(env, comp);
	else
		no_error = no_error * no_syntax_errors(comp);
	free_components(comp);
	return (no_error);
}

void		run_shell(t_vector *env, char *buf)
{
	char	**split;
	t_icomp	comp_blocks;
	size_t	i;
	size_t	j;
	int		no_error;

	split = split_unless_quote(buf, ';');
	j = 0;
	no_error = 1;
	while (j < 2)
	{
		i = 0;
		while (split[i] != NULL && no_error)
		{
			no_error = no_error * \
			parse_and_execute(env, &(split[i]), &comp_blocks, j);
			i++;
		}
		j++;
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

int			main(int ac, char **av, char **envp)
{
	t_vector	*env;

	g_ret_val = 0;
	g_amt_processes = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	env = envp_to_env(envp);
	(void)ac;
	(void)av;
	while (1)
		get_input(env);
	return (0);
}
