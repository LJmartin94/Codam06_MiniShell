/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_option_flags.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 17:19:17 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/28 12:16:10 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "flag_validation_table.h"
#include "error.h"

#include <stdio.h>

int		ft_approve_option(t_icomp **icur)
{
	if ((*icur)->opt == NULL)
		(*icur)->opt = ft_strdup((*icur)->arg);
	else
		(*icur)->opt = ft_strjoin((*icur)->opt, (*icur)->arg);
	if ((*icur)->opt == NULL)
		error_exit_errno();
	free((*icur)->arg);
	(*icur)->arg = NULL;
	return (0);
}

int		validate_option_flags(t_icomp **icur)
{
	int i;
	int j;
	int ret;

	if (ft_strlen((*icur)->arg) < 2)
		return (0);
	i = 1;
	ret = 1;
	while ((*icur)->arg[i] != '\0' && ret)
	{
		ret = 0;
		j = 0;
		while (j < FLAG_TABLE_SIZE)
		{
			if (ret == 1 || (g_flagvalid_table[j].flag == (*icur)->arg[i] && !\
					ft_strncmp(g_flagvalid_table[j].cmd, (*icur)->cmd, \
					ft_strlen((*icur)->cmd))))
				ret = 1;
			j++;
		}
		i++;
	}
	if (ret)
		ft_approve_option(icur);
	return (ret);
}
