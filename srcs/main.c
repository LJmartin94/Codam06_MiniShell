/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/24 13:47:47 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "error.h"
#include <signal.h>
#include "execute.h"

int		get_input(void)
{
	char	*buf;
	int		ret;
	t_icomp comp_blocks;

	e_write(1, "\U0001F40C ", 6);
	ret = get_next_line(STDIN_FILENO, &buf);
	if (ret == 0)
	{
		e_write(STDIN_FILENO, "\n", 1);
		exit(0);
	}
	if (ret < 0)
		error_exit_msg(C_GNL_FAIL, E_GNL_FAIL);
	parse_input(buf, &comp_blocks);
	free(buf);
	print_components(&comp_blocks);
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
	t_icomp *cmd;

	cmd = (t_icomp *)e_malloc(sizeof(t_icomp));
	cmd->cmd = "export";
	cmd->arg = "=item";
	cmd->id = 1;
	cmd->left = NULL;
	cmd->right = NULL;
	cmd->opt = NULL;
	cmd->sep = NULL;

	(void)av;
	(void)ac;
	env = convert_env(envp);
	ft_env(env);
	// ft_export(env, cmd->arg);
	// write(STDIN_FILENO, "\n\n", 2);
	ft_unset(env, "P9K_TTY");
	ft_env(env);
	// ft_unset(env, cmd);
	// ft_export(env, cmd);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		get_input();
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
