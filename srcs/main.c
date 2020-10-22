/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/24 13:06:45 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "error.h"
#include "execute.h"
#include <signal.h>
#include "execute.h"

int		get_input(void)
{
	char	*buf;
	int		ret;

	e_write(1, "\U0001F40C ", 6);
	ret = get_next_line(STDIN_FILENO, &buf);
	if (ret == 0)
	{
		e_write(STDIN_FILENO, "\n", 1);
		exit(0);
	}
	if (ret < 0)
		error_exit_msg(C_MALLOC_FAIL_LIBFT, E_MALLOC_FAIL_LIBFT);
	parse_input(buf);
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

	(void)av;
	(void)ac;
	env = convert_env(envp);
	ft_env(env);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)ac;
	(void)av;
	// (void)envp;
	t_env *env = convert_env(envp);
	(void)env;
	while (1)
		get_input();
	return (0);
}
