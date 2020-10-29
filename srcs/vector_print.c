/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_print.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 20:54:03 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/29 22:38:58 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		vector_print(int fd, t_vector *v)
{
	size_t	i;
	int		ret;
	//char	*buf;

	i = 0;
	ret = 0;
	while (i < v->amt && ret > -1)
	{
		// buf = v->data[i];
		// ret = (ret > -1) ? write(fd, buf, v->item_size) : ret;
		printf("%p\n", (v->data[i]));
		ret = (ret > -1) ? write(fd, "\n", 0) : ret;
		i++;
	}
	return (ret);
}

int		vector_debug(int fd, t_vector *v)
{
	int ret;

	ret = write(fd, "Number of items:		", 18);
	ft_putnbr_fd(v->amt, fd);
	ret = (ret > -1) ? write(fd, "\nItem size:			", 15) : ret;
	ft_putnbr_fd(v->item_size, fd);
	ret = (ret > -1) ? write(fd, "\nTotal size:			", 16) : ret;
	ft_putnbr_fd((v->amt * v->item_size), fd);
	ret = (ret > -1) ? write(fd, "\n", 1) : ret;
	if (ret > -1)
		ret = vector_print(fd, v);
	return (ret);
}
