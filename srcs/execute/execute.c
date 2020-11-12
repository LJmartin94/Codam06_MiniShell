/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/12 13:58:37 by jsaariko      ########   odam.nl         */
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
	if (ft_strncmp(comp->cmd, "cd", 4) == 0)
		return (ft_cd);
	return (NULL);
}

/*
** //TODO: Parsing needs to change for this to work
*/

static void expand(t_vector *env, t_icomp *comp)
{
	int index;
	char *final;

	final = NULL;
	if (ft_strncmp(comp->sep, "$", 2) == 0)
	{
		index = vector_search(env, compare_key, comp->right->cmd);
		if (index == -1)
		{
			return ;
		}
		t_env *item = (t_env *)vector_get(env, index);
		final = ft_strjoin(comp->arg, item->value);
	}
	if (ft_strncmp(comp->sep, "$?", 2) == 0)
	{
		char *num = ft_itoa(g_ret_val);
		final = ft_strjoin(comp->arg, num);
		free(num);
	}
	free(comp->arg);
	comp->arg = final;
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
		if (ft_strncmp(tmp->sep, "$", 1) == 0)
			expand(env, tmp);
		stdin = exec_command(env, tmp, stdin);
		tmp = tmp->right;
	}
	if (g_pid_list.amt == 0)
		free(g_pid_list.data);
	else
		ft_dprintf(STDOUT_FILENO, "something wrong with pid_list\n");//TODO: confirm and kill
}
