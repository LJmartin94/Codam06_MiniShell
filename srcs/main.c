/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/03 11:51:10 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"
#include <stdio.h>
#include <signal.h>
#include "execute.h"//TODO: remove when movign sig handler

int		get_input(t_vector *env)
{
	char	*buf;
	int		ret;
	t_icomp comp_blocks;

	// e_write(STDOUT_FILENO, "start of input", 14);
	e_write(STDOUT_FILENO, "\U0001F40C ", 6);
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
	execute(env, &comp_blocks);
	free_components(&comp_blocks);
	return (ret);
}

/*
** //TODO: also make sure to kill any ongoing process in sig_handler
*/

void	sig_handler(int signo)
{
	// size_t i;
	// i = 0;
	// int *pid_cur;
	// while (i < g_pid_list->amt)
	// {
	// 	pid_cur = (int *)vector_get(g_pid_list, i);
	// 	kill(SIGINT, *pid_cur);
	// 	free(pid_cur);
	// 	pid_cur = NULL;
	// 	vector_delete(g_pid_list, i);
	// 	i++;
	// }
	if (signo == SIGINT)
	{
		// e_write(STDOUT_FILENO, "sigint occurred", 15);
		e_write(STDOUT_FILENO, "\n", 1);
		e_write(STDOUT_FILENO, "\U0001F40C ", 6);
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
	{
		get_input(env);
	}
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
ARG:	|%s|\nSEP:	|%s|\nRGT: [%p]\n", icur->id, icur->left, icur, \
		icur->cmd, icur->opt, icur->arg, icur->sep, icur->right);
		icur = icur->right;
	}
}


//TODO: Discuss whether I should fork the whole project, so i could just exit that process on sigint
//TODO: Discuss why things are automatically killed, do i need to explicitly kill every process individually? As things already seem to be getting killed
//TODO: Discuss whether I need redirections to be parsed differently
//TODO: Discuss JUST REALIZED && is a bonus lol
//TODO: Discuss whether builtins should run in their own forks
//TODO: Discuss: Parse should fail if executable ends in a pipe
//TODO: Discuss: Parser adds strange amounts of whitespace between quotes: echo "aaa;aa | a'a aaa a aaaaaa >> aaa'a" 'aaaaa > aa || aaaaaa >> aa;'