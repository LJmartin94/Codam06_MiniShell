/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   recognise_token_state.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/20 15:11:21 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/25 16:09:56 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "recognise_transition_table.h"

t_transition_code	recognise_token_state(t_token *this)
{
	int					i;
	t_transition_code	id;

	if (this == NULL)
		return (exit_state);
	i = 0;
	id = arg;
	while (i < RECOG_TABLE_SIZE)
	{
		if (ft_strncmp((g_tokenrecog_table[i]).to_compare, this->token, \
		ft_strlen((g_tokenrecog_table[i]).to_compare)) == 0)
		{
			id = (&g_tokenrecog_table[i])->ret;
			break ;
		}
		i++;
	}
	return (id);
}
