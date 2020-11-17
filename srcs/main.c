/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/17 15:15:12 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"
#include "execute.h"

char		**split_unless_quote(char const *s, char c);

int		get_input(t_vector *env)
{
	char	*buf;
	int		ret;
	t_icomp comp_blocks;

	e_write(STDOUT_FILENO, "\U0001F40C ", 6);
	ret = get_next_line(STDIN_FILENO, &buf);
	if (ret == 0)
	{
		e_write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	if (ret < 0)
		error_exit_msg(C_GNL_FAIL, E_GNL_FAIL);
	char **split = split_unless_quote(buf, ';');
	// char **split = ft_split(buf, ';');
	size_t i;
	i = 0;
	while(split[i] != NULL)
	{
		// ft_dprintf(STDOUT_FILENO, "[%s]\n", split[i]);
		expand_env(env, &(split[i]));
		parse_input(split[i], &comp_blocks);
		i++;
		execute(env, &comp_blocks);
		free_components(&comp_blocks);
	}
	free(buf);
	free_matrix(split);
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

/*
** //TODO: remove function print_components if no longer debugging
*/

void	print_components(t_icomp *icur)
{
	while (icur)
	{
		printf("Block:	|%d|\nLFT: [%p]\nADR:	|%p|\nCMD:	|%s|\nOPT:	|%s|\n\
ARG:	|%s|\nSEP:	|%s|\nRGT: [%p]\n\n", icur->id, icur->left, icur, \
		icur->cmd, icur->opt, icur->arg, icur->sep, icur->right);
		icur = icur->right;
	}
}
