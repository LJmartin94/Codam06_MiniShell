/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/05 21:58:02 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"
#include <signal.h>

// int		write_kvp(int fd, t_env *kvp)
// {
// 	e_write(fd, kvp->key, ft_strlen(kvp->key));
// 	e_write(fd, "=", 1);
// 	e_write(fd, kvp->value, ft_strlen(kvp->value));
// 	e_write(fd, "\n", 1);
// 	return (0);
// }

int		get_input(t_vector *env)
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
	execute(env, &comp_blocks);
	// vector_debug(STDIN_FILENO, env, &write_kvp);
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
	while (icur)
	{
		printf("Block:	|%d|\nLFT: [%p]\nADR:	|%p|\nCMD:	|%s|\nOPT:	|%s|\n\
ARG:	|%s|\nSEP:	|%s|\nRGT: [%p]\n", icur->id, icur->left, icur, \
		icur->cmd, icur->opt, icur->arg, icur->sep, icur->right);
		icur = icur->right;
	}
}
