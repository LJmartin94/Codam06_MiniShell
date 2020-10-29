/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 09:39:24 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/29 12:53:05 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

/*
** //TODO: When not supplying arguments to export, dont use the env command
** export returns one if NAME is invalid
*/

static int	print_env(t_vector *env)
{
	size_t	i;
	t_env	*cur;

	i = 0;
	cur = NULL;
	while (i < env->amt)
	{
		cur = (t_env *)vector_get(env, i);
		write(STDIN_FILENO, "declare -x ", 11);
		write(STDIN_FILENO, cur->key, ft_strlen(cur->key));
		if (cur->value != NULL)
		{
			write(STDIN_FILENO, "=\"", 2);
			write(STDIN_FILENO, cur->value, ft_strlen(cur->value));
			write(STDIN_FILENO, "\"", 1);
		}
		write(STDIN_FILENO, "\n", 1);
		i++;
	}
	return (0);
}

int			ft_export(t_vector *env, t_icomp *cmd)
{
	t_env	*item;
	int		ret;
	int		env_i;	
	t_env *edit;

	env_i = 0;
	if ((ft_strncmp(cmd->arg, "", 1)) == 0)
	{
		print_env(env);
		return (0);
	}
	if (!ft_isalpha(cmd->arg[0]))
	{
		ft_dprintf(STDERR_FILENO, "export: '%s': not a valid identifier\n",
			cmd->arg);
		return (1);
	}
	item = get_env_item(cmd->arg);
	env_i = vector_search(env, compare_key, item->key);
	if (env_i != -1)
	{
		edit = vector_get(env, env_i);
		if (item->value != NULL)
		{
			free(edit->value);
			edit->value = item->value;
			free(item->key);
			free(item);
		}
		else
		{
			free(item->key);
			free(item->value);
			free(item);
		}
		
	}
	else
	{
		ret = vector_push(env, item);
		if (!ret)
			error_exit_errno();
	}
	return (0);
}
