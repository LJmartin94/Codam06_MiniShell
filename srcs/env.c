/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 11:49:12 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/27 10:19:27 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "execute.h"

/*
** //TODO: if strlcpy fails?
*/

t_env	*get_env_item(char *env_str)
{
	t_env	*item;
	int		i;
	int		shlvl;
	int		ret;

	item = (t_env *)e_malloc(sizeof(t_env));
	i = 0;
	while(env_str[i] != '=')
		i++;
	item->key = (char *)e_malloc(sizeof(char) * (i + 1));
	ret = ft_strlcpy(item->key, env_str, i + 1); //TODO: or if there's nothing behind =   ??
	if (ret == -1)
		ft_dprintf(STDERR_FILENO, "rip ft_strlcpy in get_env_item");
	if (ft_strncmp(item->key, "SHLVL", 5) == 0)
	{
		shlvl = ft_atoi(env_str + i + 1);
		shlvl++;
		item->value = ft_itoa(shlvl);
	}
	else
		item->value = ft_strdup(env_str + i + 1);
	if (item->value == NULL)
		error_exit_errno();
	return (item);
}

t_vector		*convert_env(char **envp)
{
	size_t		i;
	size_t		count;
	t_env		*cur;
	t_vector	*env;
	int			ret;

	i = 0;
	count = 0;
	cur = NULL;
	while (envp[count])
		count++;
	env = (t_vector *)e_malloc(sizeof(t_vector));
	vector_init(env);
	while (i < count)
	{
		cur = get_env_item(envp[i]);
		if (cur == NULL)
		{
			ft_dprintf(STDERR_FILENO, "ENV ITEM RETURNS NULL WHERE IT SHOULDN'T\n");
			return (NULL);
		}
		ret = vector_push(env, cur);
		
		if (!ret)
			error_exit_errno();
		i++;
	}
	return (env);
}

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

static int		validate_cmd_env(t_icomp cmd)
{
	// ft_dprintf(STDIN_FILENO, "\tcmd:\t%s\n\
	// arg:\t%s\n\
	// id:\t%d\n\
	// opt:\t%s\n\
	// sep:\t%s\n", cmd.cmd, cmd.arg, cmd.id, cmd.opt, cmd.sep);
	if (cmd.arg != NULL || cmd.opt != NULL)
		return (0);
	return (1);
}

int				ft_env(t_vector *env, t_icomp cmd)
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
		write_key_val_pair(cur->key, cur->value);
		i++;
	}
	return (0);
}
