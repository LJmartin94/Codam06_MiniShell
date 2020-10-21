/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   recognise_token_state.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/20 15:11:21 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/21 15:35:52 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "recognise_transition_table.h"

t_transition_code	recognise_token_state(t_token *this)
{
	int					i;
	t_transition_code	id;

	i = 0;
	id = arg;
	while (i < RECOG_TABLE_SIZE)
	{
		if (ft_strncmp((g_tokenrecog_table[i]).to_compare, this->token, \
		ft_strlen(this->token)) == 0)
		{
			id = (&g_tokenrecog_table[i])->ret;
			break ;
		}
		i++;
	}
	return (id);
}
