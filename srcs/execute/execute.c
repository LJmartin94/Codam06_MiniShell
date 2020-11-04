/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/04 10:47:26 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "error.h"


/*
** TODO: Build command validators in functions
*/

t_cmd	get_command(t_icomp *comp)
{
	if (ft_strncmp(comp->cmd, "echo", 5) == 0)
		return (ft_echo);
	if (ft_strncmp(comp->cmd, "env", 4) == 0)
		return (ft_env);
	if (ft_strncmp(comp->cmd, "unset", 6) == 0)
		return (ft_unset);
	if (ft_strncmp(comp->cmd, "export", 7) == 0)
		return (ft_export);
	return (NULL);
}


void	wait_for_processes()
{
	int *this_one;
	while(g_pid_list.amt > 0)//TODO: I'll probably never need this
	{
		this_one = vector_get(&g_pid_list, 0); //should make sure to wait for processes to finish in the right order, but also have processes remain open until not used anymore
		wait(this_one);
		free(this_one);
		vector_delete(&g_pid_list, 0);
		// ft_dprintf(STDOUT_FILENO, "\n\n");
	}
}

void	execute(t_vector *env, t_icomp *comp)
{
	t_icomp	*tmp;
	int 	stdin;
	int i;

	vector_init(&g_pid_list);
	i = 0;
	tmp = comp;
	stdin = -1;
	while (tmp != NULL)
	{
		stdin = exec_command(env, tmp, stdin);
		tmp = tmp->right;
		i++;
	}
}
