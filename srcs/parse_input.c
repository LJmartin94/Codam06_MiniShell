/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 12:04:04 by jsaariko      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/10/19 21:12:38 by limartin      ########   odam.nl         */
=======
/*   Updated: 2020/10/19 12:19:47 by jsaariko      ########   odam.nl         */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
<<<<<<< HEAD
#include "parse.h"
=======
>>>>>>> master

void	parse_input(const char *input)
{
	t_token *tokens;

	tokens = get_tokens(input);
	manage_fsm(tokens);
	ft_printf("%s\n", input);
}
