/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/20 18:31:57 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include<signal.h>

void	get_input(void)
{
	char *buf;
	int ret;

	write(1, "\U0001F40C", 4);
	write(1, " ", 1);
	ret = get_next_line(STDIN_FILENO, &buf);
	if (ret == 0)	//ctrl-D
	{
		ft_printf("\n"); //TODO: try not to print ^D
		exit(0);
	}
	parse_input(buf);
}

void sig_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	write(1, "\U0001F40C", 4);
	write(1, " ", 1);
	//TODO: also make sure to kill any ongoing process
}

int		main(void)
{
	signal(SIGINT, sig_handler);
	while(1)
		get_input();
	return (0);
}
