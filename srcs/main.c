/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/08 12:15:51 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"
#include "execute.h"

void	run_shell(t_vector *env, char *buf)
{
	char	**split;
	t_icomp	comp_blocks;
	size_t	i;

	split = split_unless_quote(buf, ';');
	i = 0;
	while (split[i] != NULL)
	{
		expand_env(env, &(split[i]));
		parse_input(split[i], &comp_blocks);
		i++;
		execute(env, &comp_blocks);
		free_components(&comp_blocks);
	}
	free_matrix(split);
}

int		get_input(t_vector *env)
{
	char	*buf;
	int		ret;

	// e_write(STDOUT_FILENO, "\U0001F40C ", 6);
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

int		main(int ac, char **av, char **envp)
{
	t_vector	*env;

	g_ret_val = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	env = envp_to_env(envp);
	(void)ac;
	(void)av;
	while (1)
		get_input(env);
	return (0);
}
