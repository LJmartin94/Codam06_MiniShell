/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/15 12:06:33 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	get_input(void)
{
	char *buf;

	// ft_printf("sup? ");
	write(1, "\U0001F40C", 4);
	write(1, " ", 1);
	get_next_line(1, &buf);
	parse_input(buf);
}

int		main(void)
{
	while (1)
		get_input();
	return (0);
}
