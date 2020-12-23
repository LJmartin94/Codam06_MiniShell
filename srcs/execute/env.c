/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 11:49:12 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/09 14:07:01 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "execute.h"

static void		write_key_val_pair(char *key, char *value, int fd)
{
	e_write(fd, key, ft_strlen(key));
	e_write(fd, "=", 1);
	e_write(fd, value, ft_strlen(value));
	e_write(fd, "\n", 1);
}

static int		validate_cmd_env(t_icomp *cmd)
{
	if (ft_strncmp(cmd->arg->value, "", 1) != 0 || \
	ft_strncmp(cmd->opt, "", 1) != 0)
		return (0);
	return (1);
}

int				ft_env(t_vector *env, t_icomp *cmd, int fd)
{
	size_t	i;
	t_env	*cur;

	i = 0;
	cur = NULL;
	if (validate_cmd_env(cmd) == 0)
	{
		cmd_error(cmd, "Bad params");
		return (127);
	}
	while (i < env->amt)
	{
		cur = (t_env *)vector_get(env, i);
		if (cur->value != NULL)
			write_key_val_pair(cur->key, cur->value, fd);
		i++;
	}
	return (0);
}
