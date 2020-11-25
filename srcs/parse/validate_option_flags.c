/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_option_flags.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 17:19:17 by limartin      #+#    #+#                 */
/*   Updated: 2020/11/25 17:58:01 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "flag_validation_table.h"
#include "error.h"

int			ft_approve_option(t_icomp **icur)
{
	char	*new_val;
	t_arg	*opt_link;
	t_arg	*arg_link;

	opt_link = (*icur)->arg;
	while (1)
	{
		new_val = ft_strjoin((*icur)->opt, (opt_link)->value);
		if (new_val == NULL)
			error_exit_errno();
		free((*icur)->opt);
		(*icur)->opt = new_val;
		if (opt_link->pad[0] == '\0' && opt_link->right != NULL)
			opt_link = opt_link->right;
		else
			break ;
	}
	arg_link = opt_link->right;
	if (arg_link == NULL)
	{
		arg_link = (t_arg *)e_malloc(sizeof(t_arg));
		ft_argconst(arg_link);
	}
	opt_link->right = NULL;
	free_args((*icur)->arg);
	(*icur)->arg = arg_link;
	return (0);
}

static int	single_char_flag(t_icomp **icur, int i, int j)
{
	size_t	cmd_len;
	t_arg	*last;

	last = (*icur)->arg;
	while (last->right != NULL)
		last = last->right;
	cmd_len = ft_strlen((*icur)->cmd);
	if (cmd_len != ft_strlen(g_flagvalid_table[j].cmd))
		return (0);
	if (ft_strncmp(g_flagvalid_table[j].cmd, (*icur)->cmd, cmd_len))
		return (0);
	if (g_flagvalid_table[j].flag[0] != (last)->value[i])
		return (0);
	return (1);
}

int			validate_option_flags(t_icomp **icur)
{
	int		i;
	int		j;
	int		ret;
	t_arg	*link;

	i = 0;
	ret = 1;
	link = (*icur)->arg;
	if (link->value[0] == '\0')
		return (0);
	if ((*icur)->arg->value[0] == '-')
		i++;
	else
		ret = 0;
	while (ret)
	{
		if (link != (*icur)->arg)
			i = 0;
		while ((link)->value[i] != '\0' && ret)
		{
			ret = 0;
			j = 0;
			while (j < FLAG_TABLE_SIZE)
			{
				if (ret == 1 || single_char_flag(icur, i, j))
					ret = 1;
				j++;
			}
			i++;
		}
		if (link->pad[0] == '\0' && link->right != NULL)
			link = link->right;
		else
			break ;
	}
	ret--;
	i = (link != (*icur)->arg || ft_strlen((link)->value) >= 2) ? 1 : 0;
	if (ret == 0 && i)
	{
		ft_approve_option(icur);
		ret++;
	}
	else if (ret == 0 && link->pad[0] != '\0')
		ret--;
	return (ret);
}
