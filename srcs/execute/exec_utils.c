/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 10:41:34 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/06 10:44:01 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//TODO: murder?

#include "libft.h"

int pid_print(int fd, int *pid)//
{
	return (ft_dprintf(fd, "pid: %d\n", *pid));
}

int	cmp_pid(int *pid1, int *pid2)
{
	return (*pid1 - *pid2);
}

void free_matrix(char **matrix)
{
	size_t i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
}