/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/04 14:29:06 by jsaariko      ########   odam.nl         */
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

int pid_print(int fd, int *pid)
{
	return (ft_dprintf(fd, "pid: %d\n", *pid));
}

int	send_signal_to_processes(int signo)
{
	int *this_one;
	int ret = 0;
	// vector_debug(STDOUT_FILENO, &g_pid_list, pid_print);
	// ft_dprintf(STDOUT_FILENO, "amt processes: %d\n", g_pid_list.amt);
	if (g_pid_list.amt == 0)
	{
		ft_dprintf(STDOUT_FILENO, "amt: 0 == amt %d\n", g_pid_list.amt);
		return (ret);
	}
	// while(g_pid_list.amt > 0)//TODO: I'll probably never need this
	// {
		// ft_dprintf(STDOUT_FILENO, "cur amt in free: %d\n", g_pid_list.amt);
		this_one = vector_get(&g_pid_list, 0); //should make sure to wait for processes to finish in the right order, but also have processes remain open until not used anymore
		// wait(this_one);
		kill(*this_one, signo);
			// ret = 1;
		// else
			// ft_dprintf(STDOUT_FILENO, "(return of kill is not 0)");
		// free(this_one);
		// vector_delete(&g_pid_list, 0);
		// ft_dprintf(STDOUT_FILENO, "\n\n");
	// }
	return (1);
}

void	handle_sigint(int signo)
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
		if (g_pid_list.amt == 0)
		{
			e_write(STDOUT_FILENO, "\U0001F40C ", 6); 
		}
	}
}

void	handle_sigquit(int signo)
{
	if (signo == SIGQUIT)
	{
		if (g_pid_list.amt != 0)
			e_write(STDOUT_FILENO, "Quit: \n", 7);
	}
}

int		main(int ac, char **av, char **envp)
{
	t_vector *env;

	signal(SIGINT, handle_sigint); //TODO: Should stop current and all future processes
	signal(SIGQUIT, handle_sigquit); //TODO: Should quit current processes
	// signal(SIGQUIT, SIG_IGN); //TODO: Should quit current processes
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
//TODO: Parsing: Have redirections as it's own separate part, preferably with an enum, and then the param of the redirection as a separate part as well on icomp. Pipe can remain as a separator?