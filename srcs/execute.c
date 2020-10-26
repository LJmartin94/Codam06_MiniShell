/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/26 17:03:10 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "parse.h"
#include "libft.h"



//get_command() <- check which command was ran and pass argument to said command

void	get_command(t_vector *env, t_icomp cmd)
{
	if (ft_strncmp(cmd.cmd, "env", 4) == 0) // TODO: Make sure cmd.cmd is not envd and accepted
		ft_env(env);
	if (ft_strncmp(cmd.cmd, "unset", 6) == 0)
		ft_unset(env, cmd.arg);
	if (ft_strncmp(cmd.cmd, "export", 7) == 0)
		ft_export(env, cmd.arg);
}

void	execute(t_vector *env, t_icomp cmd) //Rotate through the commands
{
	get_command(env, cmd);
	// t_icomp *tmp = &cmd;

	// while (cmd != NULL)
	// {
		// get_command(env, tmp);
		// tmp = (*tmp).right;
	// }
	// int ret;

	// (void)cmd;
	// ft_env(env);
	// ft_dprintf(STDIN_FILENO, "\n\nbreaks here???????\n\n");
	// ft_export(env, cmd->arg);
	// write(STDIN_FILENO, "\n\n", 2);
	// ft_dprintf(STDIN_FILENO, "\n");
	// ft_export(env, "lol=lol");
	// ft_dprintf(STDIN_FILENO, "\n");
	// ft_unset(env, "P9K_TTY");
	// ft_env(env);
	// ft_unset(env, cmd);
	// ft_export(env, cmd);


	// if (ft_strncmp(cmd.cmd, "env", 3) == 0)
		// ret = ft_env(env);
}
