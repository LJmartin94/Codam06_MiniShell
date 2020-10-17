/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/19 16:04:28 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
// #include "minishell.h"

int	get_input(void)
{
	char *buf;
	int ret;

	// ft_printf("sup? ");
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
