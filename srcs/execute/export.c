/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 09:39:24 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/07 13:19:59 by jsaariko      ########   odam.nl         */
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

// static void	edit_env(t_vector *env, t_env *item, int pos)
// {
// 	t_env	*edit;

// 	if (pos != -1)
// 	{
// 		edit = vector_get(env, pos);
// 		if (item->value != NULL)
// 		{
// 			free(edit->value);
// 			edit->value = item->value;
// 			free(item->key);
// 			item->key = NULL;
// 			free(item);
// 			item = NULL;
// 		}
// 		else
// 		{
// 			free_env_item(item);
// 			item = NULL;
// 		}
// 	}
// 	else
// 	{
// 		if (vector_push(env, item) == 0)
// 			error_exit_errno();
// 	}
// }


/*
** // TODO: export returns an exit status of 0 unless an invalid
** // option is encountered, one of the names is not a valid shell variable name
** // can export multiple variables at once
** // export "lol lol" <- returns 1, not a valid identifier
** // split by whitespaces. If there are whitespaces between quotes, s no good
** // TODO: Make sure export "" returns invalid and export prints env
*/

static int validate_export(t_env *item)
{
	if (validate_env_key(item->key) == 1)//TODO: do this until =, no further
		return (1);
	return (0);
}

char *join_args(t_arg **arg)
{
	char *str;
	char *str2;

	str = ft_strdup((*arg)->value);
	while((*arg)->pad[0] == '\0' && (*arg)->right != NULL)
	{
		str2 = ft_strjoin(str, (*arg)->right->value);
		free(str);
		str = ft_strdup(str2);
		free(str2);
		(*arg) = (*arg)->right;
	}
	return (str);
}

/*
** //TODO [export 1test] should have exit status of 1
*/

int ft_export(t_vector *env, t_icomp *cmd, int fd)
{
	t_arg *arg;

	arg = cmd->arg;
	if (arg->value[0] == '\0')
		print_env(env, fd);
	else
	{
		while (arg)
		{
			char *item = join_args(&arg);
			t_env *env_item = get_env_item(item);
			free(item);
			if (env_item->key[ft_strlen(env_item->key) - 1] == '+')
			{
				char *ptr = (char *)e_malloc(sizeof(char) * ft_strlen(env_item->key));
				ft_strlcpy(ptr, env_item->key, ft_strlen(env_item->key));
				free(env_item->key);
				env_item->key = ptr;
				int pos = vector_search(env, compare_key, env_item->key);
				if (validate_export(env_item) == 0)
				{
					t_env *thingy = vector_get(env, pos);
					// ft_dprintf(STDOUT_FILENO, "%p\n", thingy);
					if (thingy == NULL)
					{
						edit_env(env, env_item, pos);
					}
					else
					{
						char *another;
						if (thingy->value != NULL)
						{
							another = ft_strsplice(thingy->value, ft_strlen(thingy->value), 0, env_item->value);
							free(thingy->value);
						}
						else
						{
							another = ft_strdup(env_item->value);
						}
						thingy->value = another;
					}
				}
				else
					cmd_error(cmd, "Invalid argument", fd);
			}
			else
			{
				int pos = vector_search(env, compare_key, env_item->key);
				if (validate_export(env_item) == 0)
					edit_env(env, env_item, pos);
				else
					cmd_error(cmd, "Invalid argument", fd);
			}
			arg = arg->right;
		}
	}
	return (0);
}