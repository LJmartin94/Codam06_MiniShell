/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/13 11:10:18 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"
#include <signal.h>

int		get_input(t_vector *env)
{
	char	*buf;
	int		ret;
	t_icomp comp_blocks;

	e_write(1, "\U0001F40C ", 6);
	ret = get_next_line(STDIN_FILENO, &buf);
	if (ret == 0)
	{
		e_write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	if (ret < 0)
		error_exit_msg(C_GNL_FAIL, E_GNL_FAIL);
	parse_input(buf, &comp_blocks);
	free(buf);
	print_components(&comp_blocks);
	execute(env, &comp_blocks);
	free_components(&comp_blocks);
	return (ret);
}

/*
** //TODO: also make sure to kill any ongoing process in sig_handler
*/

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		e_write(1, "\n", 1);
		e_write(1, "\U0001F40C ", 6);
	}
}

int		main(int ac, char **av, char **envp)
{
	t_vector *env;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
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
			to_print = icur->arg->right;
		}
		printf("Arg-string: |");
		to_print = icur->arg;
		while (to_print != NULL)
		{
			printf("%s%s", to_print->value, to_print->pad);
			to_print = icur->arg->right;
		}
		printf("|\n");
		icur = icur->right;
	}
}
