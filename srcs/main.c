/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/21 10:51:30 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include <signal.h>

void	get_input(void)
{
	char	*buf;
	int		ret;

	write(1, "\U0001F40C ", 6);
	ret = get_next_line(STDIN_FILENO, &buf);
	if (ret == 0)
	{
		ft_printf("\n");
		exit(0);
	}
	parse_input(buf);
}

/*
** //TODO: also make sure to kill any ongoing process in sig_handler
*/

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		write(1, "\U0001F40C ", 6);
	}
}

int		main(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		get_input();
	return (0);
}
