/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/19 15:23:50 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"

void	get_input(void)
{
	char *buf;

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
