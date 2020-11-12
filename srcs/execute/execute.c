/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/12 18:24:22 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "error.h"
#include "t_string.h"

/*
** TODO: Build command validators in functions
*/

// $? is the most recent foreground pipeline exit status.

t_cmd	get_command(t_icomp *comp)
{
	if (ft_strncmp(comp->cmd, "echo", 5) == 0)
		return (ft_echo);
	if (ft_strncmp(comp->cmd, "exit", 5) == 0)
		return (ft_exit);
	if (ft_strncmp(comp->cmd, "env", 4) == 0)
		return (ft_env);
	if (ft_strncmp(comp->cmd, "unset", 6) == 0)
		return (ft_unset);
	if (ft_strncmp(comp->cmd, "export", 7) == 0)
		return (ft_export);
	if (ft_strncmp(comp->cmd, "pwd", 4) == 0)
		return (ft_pwd);
	if (ft_strncmp(comp->cmd, "cd", 4) == 0)
		return (ft_cd);
	return (NULL);
}

/*
** //TODO: Parsing needs to change for this to work
*/

char *env_replace(char *orig, char *pos, t_env *replace)
{
	char *new;
	t_string str;

	str.len = ft_strlen(orig);
	str.string = ft_strdup(orig);
	if (replace == NULL)
		string_splice(&str, pos - orig, 1, "");
	else
		string_splice(&str, pos - orig, ft_strlen(replace->key) + 1, replace->value);
	new = str.string;
	return (new);
}

t_env *expand_value(t_vector *env, char *pos)
{
	(void)env;
	int len;
	char *key;
	len = ft_strchrset(pos, " ");
	if (len > 0)
	{
		key = (char *)e_malloc(sizeof(char) * len + 1); //TODO: or not + 1?
		key = ft_memcpy(key, pos, sizeof(char) * len);
	}
	else
		key = ft_strdup(pos);
	int index = vector_search(env, compare_key, key);
	t_env *item = vector_get(env, index);
	if (item == NULL)
	{
		item = (t_env *)e_malloc(sizeof(t_env));
		item->key = key;//TODO: in some cases add a space
		item->value = ft_strdup("");
	}
	return (item);
}

static void expand(t_vector *env, t_icomp *comp)
{
	char *final;

	final = NULL;
	// char *pos;
	size_t i = 0;
	while (comp->arg[i] != '\0')
	{
		if (comp->arg[i] == '$')
		{
			if (comp->arg[i + 1] == '?')
			{
				t_string lol;
				lol.string = ft_strdup(comp->arg);
				lol.len = ft_strlen(comp->arg);

				string_splice(&lol, i, 2, ft_itoa(g_ret_val));
				free(comp->arg);
				comp->arg = lol.string;
			}
			else
			{
				t_env *replace;
				replace = expand_value(env, comp->arg + i + 1);
				final = env_replace(comp->arg, comp->arg + i, replace);
				// ft_dprintf(STDOUT_FILENO, "final: %s\n", final);
				free(comp->arg);
				comp->arg = final;
			}
			// free(comp->arg);
			// comp->arg = final;
		}
		i++;
	}
}

void	execute(t_vector *env, t_icomp *comp)
{
	t_icomp	*tmp;
	int		stdin;

	vector_init(&g_pid_list);
	tmp = comp;
	stdin = -1;
	while (tmp != NULL)
	{
		expand(env, tmp);
		stdin = exec_command(env, tmp, stdin);
		tmp = tmp->right;
	}
	if (g_pid_list.amt == 0)
		free(g_pid_list.data);
	else
		ft_dprintf(STDOUT_FILENO, "something wrong with pid_list\n");//TODO: confirm and kill
}
