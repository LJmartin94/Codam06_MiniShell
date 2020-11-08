/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 11:49:12 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/08 18:04:13 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "execute.h"

static void		write_key_val_pair(char *key, char *value)
{
	e_write(STDOUT_FILENO, key, ft_strlen(key));
	e_write(STDOUT_FILENO, "=", 1);
	e_write(STDOUT_FILENO, value, ft_strlen(value));
	e_write(STDOUT_FILENO, "\n", 1);
}

/*
** //TODO: how can env fail and what is the return value:
** returns >0 if error occurs, 126 if env is not able to be used 127
** if env was not found
** illegal option returns 1
** bad file returns 127
*/

static int		validate_cmd_env(t_icomp *cmd)
{
	if (ft_strncmp(cmd->arg, "", 1) != 0 || ft_strncmp(cmd->opt, "", 1) != 0)
		return (0);
	return (1);
}

int				ft_env(t_vector *env, t_icomp *cmd)
{
	size_t	i;
	t_env	*cur;

	i = 0;
	cur = NULL;
	if (validate_cmd_env(cmd) == 0)
	{
		invalid_cmd(cmd);
		return (127);
	}
	while (i < env->amt)
	{
		cur = (t_env *)vector_get(env, i);
		if (cur->value != NULL)
			write_key_val_pair(cur->key, cur->value);
		i++;
	}
	return (0);
}
