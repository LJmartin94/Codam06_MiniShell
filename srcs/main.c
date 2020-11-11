/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/11 16:13:58 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

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
	parse_input(buf, &comp_blocks);
	free(buf);
	// print_components(&comp_blocks);
	execute(env, &comp_blocks);
	free_components(&comp_blocks);
	return (ret);
}

/*
** //TODO Change what to do with ac, av??
*/
int			g_ret_val; //TODO: move

int		main(int ac, char **av, char **envp)
{
	t_vector	*env;

	g_ret_val = 0; //TODO: fixes issue but won't compile on linux?
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

//TODO: Discuss why things are automatically killed, do i need to explicitly kill every process individually? As things already seem to be getting killed
//TODO: Discuss: Parse should fail if executable ends in a pipe
//TODO: Discuss: parser should separate separate arguments into an array of arguments
//TODO: shouldnt be parsed as separator $?
//TODO: shouldnt be parsed as separator $
//TODO: Discuss how to parse $. Examples:
// echo whazzup $USER lol -> whazzup jules lol
// echo "whazzup $USER lol" -> whazzup jules lol
// echo "whazzup $USE lol" -> whazzup  lol <-- (two spaces in the middle)
// echo 'whazzup $USER lol' -> whazzup $USER lol
