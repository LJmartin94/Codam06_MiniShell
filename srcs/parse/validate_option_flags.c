/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_option_flags.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 17:19:17 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/08 17:56:58 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "flag_validation_table.h"
#include "error.h"

int			ft_approve_option(t_icomp **icur)
{
	char *new_val;

	new_val = ft_strjoin((*icur)->opt, (*icur)->arg);
	if (new_val == NULL)
		error_exit_errno();
	free((*icur)->opt);
	(*icur)->opt = new_val;
	free((*icur)->arg);
	(*icur)->arg = empty_string_alloc();
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
	if (g_flagvalid_table[j].flag[0] != (*icur)->arg[i])
		return (0);
	return (1);
}

static int	multi_char_flag(t_icomp **icur, int j)
{
	size_t	cmd_len;
	size_t	opt_len;

	cmd_len = ft_strlen((*icur)->cmd);
	opt_len = ft_strlen((*icur)->arg);
	if (opt_len < 4)
		return (0);
	if (cmd_len != ft_strlen(g_flagvalid_table[j].cmd))
		return (0);
	if (ft_strncmp(g_flagvalid_table[j].cmd, (*icur)->cmd, cmd_len))
		return (0);
	if ((*icur)->arg[1] != '-')
		return (0);
	if (ft_strncmp(g_flagvalid_table[j].flag, (*icur)->arg + 2, opt_len))
		return (0);
	return (1);
}

int			validate_option_flags(t_icomp **icur)
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
