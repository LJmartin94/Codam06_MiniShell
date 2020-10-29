/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 11:49:12 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/29 11:30:51 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "execute.h"

/*
** //TODO: if strlcpy fails?
*/

static void		write_key_val_pair(char *key, char *value)
{
	write(STDIN_FILENO, key, ft_strlen(key));
	write(STDIN_FILENO, "=", 1);
	write(STDIN_FILENO, value, ft_strlen(value));
	write(STDIN_FILENO, "\n", 1);
}

/*
** //TODO: how can env fail and what is the return value:
** returns >0 if error occurs, 126 if env is not able to be used 127
** if env was not found
*/

static int		validate_cmd_env(t_icomp *cmd)
{
	// ft_dprintf(STDIN_FILENO, "\tcmd:\t%s\n\
	// arg:\t%s\n\
	// id:\t%d\n\
	// opt:\t%s\n\
	// sep:\t%s\n", cmd.cmd, cmd.arg, cmd.id, cmd.opt, cmd.sep);
	// if (cmd->arg[0] != '\0' || cmd->opt[0] != '\0')
		// return (0);
	// return (1);
	(void)cmd;
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
		return(0); //TODO: What's the return code for invalid env command? I think it's still 0
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
