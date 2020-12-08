/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 09:39:24 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/08 11:52:04 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_export.h"
#include "error.h"

/*
** //TODO: When not supplying arguments to export, dont use the env command
** export returns one if NAME is invalid
** //TODO [export 1test] should have exit status of 1
*/

static void	edit_value(t_env *old_item, t_env *new_item)
{
	char	*new_value;

	if (old_item->value != NULL)
	{
		new_value = ft_strsplice(old_item->value,
			ft_strlen(old_item->value),
			0,
			new_item->value);
		if (new_value == NULL)
			error_exit_errno();
		free(old_item->value);
	}
	else
		new_value = ft_strdup(new_item->value);
	old_item->value = new_value;
	free_env_item(new_item);
}

static int	concat_env_item(t_vector *env, t_env *new_item)
{
	t_env	*old_item;
	char	*new_key;

	new_key = ft_strsplice(new_item->key,
		ft_strlen(new_item->key) - 1, 1, "\0");
	if (new_key == NULL)
		error_exit_errno();
	free(new_item->key);
	new_item->key = new_key;
	if (validate_env_key(new_item->key) == 0)
	{
		old_item = vector_get(env, vector_search(env, compare_key,
			new_item->key));
		if (old_item == NULL)
			edit_env(env, new_item, -1);
		else
			edit_value(old_item, new_item);
	}
	else
		return (-1);
	return (1);
}

static void	manage_export(t_vector *env, t_icomp *cmd, t_arg *arg, int fd)
{
	char	*joint_arg;
	int		pos;
	t_env	*env_item;

	joint_arg = export_join_args(&arg);
	env_item = get_env_item(joint_arg);
	free(joint_arg);
	if (env_item->key[ft_strlen(env_item->key) - 1] == '+')
	{
		if (concat_env_item(env, env_item) == -1)
			cmd_error(cmd, "Invalid argument", fd);
	}
	else
	{
		pos = vector_search(env, compare_key, env_item->key);
		if (validate_env_key(env_item->key) == 0)
			edit_env(env, env_item, pos);
		else
			cmd_error(cmd, "Invalid argument", fd);
	}
}

int			ft_export(t_vector *env, t_icomp *cmd, int fd)
{
	t_arg	*arg;

	arg = cmd->arg;
	if (arg->value[0] == '\0')
		env_no_params(env, fd);
	else
	{
		while (arg)
		{
			manage_export(env, cmd, arg, fd);
			arg = arg->right;
		}
	}
	return (0);
}
