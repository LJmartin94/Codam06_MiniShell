/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/10/21 14:58:46 by limartin      ########   odam.nl         */
=======
/*   Updated: 2020/10/19 15:52:31 by jsaariko      ########   odam.nl         */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"

int		get_input(void)
{
	char	*buf;
	int		ret;

<<<<<<< HEAD
	ret = write(1, "\U0001F40C", 4);
	ret = write(1, " ", 1);
=======
	write(1, "\U0001F40C", 4);
	write(1, " ", 1);
>>>>>>> master
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
