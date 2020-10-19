/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/19 18:52:53 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"

int	get_input(void)
{
	char *buf;
	int ret;

	ret = write(1, "\U0001F40C", 4);
	ret = write(1, " ", 1);
	get_next_line(1, &buf);
	parse_input(buf);
	return (ret);
}

int		main(void)
{
	while (1)
		get_input();
	return (0);
}
