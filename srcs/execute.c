/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/22 16:49:37 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "parse.h"

void	write_key_val_pair(char *key, char *val)
{
	write(1, key, ft_strlen(key));
	write(1, "=", 1);
	write(1, val, ft_strlen(val));
}

int		ft_env(t_vector *env)
{
	int		i;
	t_env	*cur;

	i = 0;
	while (i < env->amt)
	{
		cur = (t_env *)vector_get(env, i);
		i++;
	}
}

void	execute(t_vector *env, t_icomp *cmd)
{
	int ret;

	if (ft_strncmp(cmd->cmd, "env", 3) == 0)
		ret = ft_env(env);
}