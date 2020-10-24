/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/23 12:57:06 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "parse.h"
#include "libft.h"

void	execute(t_vector *env, t_icomp *cmd)
{
	int ret;

	if (ft_strncmp(cmd->cmd, "env", 3) == 0)
		ret = ft_env(env);
}
