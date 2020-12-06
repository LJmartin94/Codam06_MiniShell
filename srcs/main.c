/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/05 10:15:32 by lindsay       ########   odam.nl         */
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
		print_components(&comp_blocks);
		execute(env, &comp_blocks);
		free_components(&comp_blocks);
	}
	free_matrix(split);
}

int		get_input(t_vector *env)
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

int		main(int ac, char **av, char **envp)
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

/*
** //TODO: remove function print_components if no longer debugging
*/

void	print_components(t_icomp *icur)
{
	t_arg *to_print;
	t_redir *rd_to_print;

	while (icur)
	{
		printf("Block:	|%d|\nLFT: [%p]\nADR:	|%p|\nCMD:	|%s|\nOPT:	|%s|\n\
ARG:	|L/L|\nSEP:	|%s|\nRGT: [%p]\n", icur->id, icur->left, icur, \
		icur->cmd, icur->opt, icur->sep, icur->right);
		to_print = icur->arg;
		while (to_print != NULL)
		{
			printf("	Arg-block:	|%d|\n	Arg-LFT:	[%p]\n\
	Arg-ADR:	|%p|\n	Arg-STATE:	|%s|\n	Arg-VAL:	|%s|\n\
	Arg-PAD:	|%s|\n	Arg-RGT:	[%p]\n", to_print->id, to_print->left, \
	to_print, to_print->type, to_print->value, to_print->pad, to_print->right);
			to_print = to_print->right;
		}
		printf("Arg-string: |");
		to_print = icur->arg;
		while (to_print != NULL)
		{
			printf("%s%s", to_print->value, to_print->pad);
			to_print = to_print->right;
		}
		printf("|\n");
		rd_to_print = icur->rdhead;
		while (rd_to_print != NULL)
		{
			printf("		redir-LFT:	[%p]\n\
		redir-ADR:	|%p|\n		redir-IN:	|%s|\n		redir-OUT:	|%s|\n		redir-FILE:	|%s|\n\
		redir-RGT:	[%p]\n", rd_to_print->left, \
			rd_to_print, rd_to_print->type_in, rd_to_print->type_out, rd_to_print->file, rd_to_print->right);
			rd_to_print = rd_to_print->right;
		}
		icur = icur->right;
	}
}
