/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_option_flags.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 17:19:17 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/13 09:27:05 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "flag_validation_table.h"
#include "error.h"

int			ft_approve_option(t_icomp **icur)
{
	char *new_val;

	new_val = ft_strjoin((*icur)->opt, ((*icur)->arg)->value);
	if (new_val == NULL)
		error_exit_errno();
	free((*icur)->opt);
	(*icur)->opt = new_val;
	free(((*icur)->arg)->value);
	((*icur)->arg)->value = ft_strdup("");
	if (((*icur)->arg)->value == NULL)
		error_exit_errno();
	return (0);
}

static int	single_char_flag(t_icomp **icur, int i, int j)
{
	size_t	cmd_len;

	cmd_len = ft_strlen((*icur)->cmd);
	if (cmd_len != ft_strlen(g_flagvalid_table[j].cmd))
		return (0);
	if (ft_strncmp(g_flagvalid_table[j].cmd, (*icur)->cmd, cmd_len))
		return (0);
	if (g_flagvalid_table[j].flag[0] != ((*icur)->arg)->value[i])
		return (0);
	return (1);
}

static int	multi_char_flag(t_icomp **icur, int j)
{
	size_t	cmd_len;
	size_t	opt_len;

	cmd_len = ft_strlen((*icur)->cmd);
	opt_len = ft_strlen(((*icur)->arg)->value);
	if (opt_len < 4)
		return (0);
	if (cmd_len != ft_strlen(g_flagvalid_table[j].cmd))
		return (0);
	if (ft_strncmp(g_flagvalid_table[j].cmd, (*icur)->cmd, cmd_len))
		return (0);
	if (((*icur)->arg)->value[1] != '-')
		return (0);
	if (ft_strncmp(g_flagvalid_table[j].flag, ((*icur)->arg)->value + 2, \
	opt_len))
		return (0);
	return (1);
}

int			validate_option_flags(t_icomp **icur)
{
	int i;
	int j;
	int ret;

	if (ft_strlen(((*icur)->arg)->value) < 2)
		return (0);
	i = 1;
	ret = 1;
	while (((*icur)->arg)->value[i] != '\0' && ret)
	{
		ret = 0;
		j = 0;
		while (j < FLAG_TABLE_SIZE)
		{
			if (ret == 1 || single_char_flag(icur, i, j) || \
			multi_char_flag(icur, j))
				ret = 1;
			j++;
		}
		i++;
	}
	if (ret)
		ft_approve_option(icur);
	return (ret);
}
