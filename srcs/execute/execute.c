/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/13 12:22:42 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "error.h"

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
	if (ft_strncmp(comp->cmd, "cd", 3) == 0)
		return (ft_cd);
	return (NULL);
}

/*
** //TODO: Parsing needs to change for this to work
*/


//TODO: Discuss, do we need to do _?
char *env_replace(char *orig, char *pos, t_env *replace)
{
	char *new;

	// ft_dprintf(STDOUT_FILENO, "orig: %s\n pos - orig: %d\nft_strlen(replace->key + 2: %d\n replace->value: %s\n\n", orig, pos - orig, ft_strlen(replace->key) + 2, replace->value);
	if (replace->value[0] == '\0')
		new = ft_strsplice(orig, pos - orig, ft_strlen(replace->key) + 2, replace->value);
	else
		new = ft_strsplice(orig, pos - orig, ft_strlen(replace->key) + 1, replace->value);
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
	size_t i = 0;
	while (comp->arg[i] != '\0')
	{
		if (comp->arg[i] == '$')
		{
			if (comp->arg[i + 1] == '?')
			{
				char *lol;
				lol = ft_strsplice(comp->arg, i, 2, ft_itoa(g_ret_val));
				free(comp->arg);
				comp->arg = lol;
				i += 2;
			}
			else
			{
				t_env *replace;
				replace = expand_value(env, comp->arg + i + 1);
				final = env_replace(comp->arg, comp->arg + i, replace);
				free(comp->arg);
				comp->arg = final;
				i = i - (ft_strlen(replace->key) + 1) + ft_strlen(replace->value);
			}
		}
		else
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
