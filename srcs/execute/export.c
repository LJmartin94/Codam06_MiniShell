/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 09:39:24 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/13 13:52:45 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

/*
** //TODO: When not supplying arguments to export, dont use the env command
** export returns one if NAME is invalid
*/

static int	print_env(t_vector *env, int fd)
{
	size_t	i;
	t_env	*cur;

	i = 0;
	cur = NULL;
	while (i < env->amt)
	{
		cur = (t_env *)vector_get(env, i);
		e_write(fd, "declare -x ", 11);
		e_write(fd, cur->key, ft_strlen(cur->key));
		if (cur->value != NULL)
		{
			e_write(fd, "=\"", 2);
			e_write(fd, cur->value, ft_strlen(cur->value));
			e_write(fd, "\"", 1);
		}
		e_write(fd, "\n", 1);
		i++;
	}
	return (0);
}

static void	edit_env(t_vector *env, t_env *item, int pos)
{
	t_env	*edit;

	if (pos != -1)
	{
		edit = vector_get(env, pos);
		if (item->value != NULL)
		{
			free(edit->value);
			edit->value = item->value;
			free(item->key);
			item->key = NULL;
			free(item);
			item = NULL;
		}
		else
		{
			free_env_item(item);
			item = NULL;
		}
	}
	else
	{
		if (vector_push(env, item) == 0)
			error_exit_errno();
	}
}

/*
** // TODO: export returns an exit status of 0 unless an invalid
** // option is encountered, one of the names is not a valid shell variable name
** // can export multiple variables at once
** // export "lol lol" <- returns 1, not a valid identifier
** // split by whitespaces. If there are whitespaces between quotes, s no good
*/

int			ft_export(t_vector *env, t_icomp *cmd, int fd)
{
	t_env	*item;
	int		pos;

	pos = 0;
	if ((ft_strncmp(cmd->arg, "", 1)) == 0)
	{
		print_env(env, fd);
		return (0);
	}
	if (!ft_isalpha(cmd->arg[0]))
	{
		ft_dprintf(STDERR_FILENO, "export: '%s': not a valid identifier\n",
			cmd->arg);
		return (1);
	}
	item = get_env_item(cmd->arg);
	pos = vector_search(env, compare_key, item->key);
	edit_env(env, item, pos);
	return (0);
}
