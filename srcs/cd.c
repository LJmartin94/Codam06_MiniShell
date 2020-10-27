/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 11:29:48 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/27 12:31:54 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"
#include <unistd.h>

int	validate_cmd_pwd(t_icomp cmd)
{
	if (cmd.opt != NULL) //pwd ignores arguments entirely. If given option, it says invalid option
		return (0);
	return (1);
}

int ft_pwd(t_vector *env, t_icomp cmd)
{
	char *dir = NULL;
	
	(void)env;
	if (validate_cmd_pwd(cmd) == 0)
	{
		invalid_cmd(cmd);
		return (0);
	}
	dir = getcwd(dir, 0);
	e_write(STDIN_FILENO, dir, ft_strlen(dir));
	e_write(STDIN_FILENO, "\n", 1);
	return (0);
}

int	ft_cd(t_vector *env, t_icomp cmd) //TODO: To test this, parsing has to work
{
	(void)env;
	(void)cmd;
	int ret = chdir(cmd.arg);
	ft_dprintf(STDIN_FILENO, "[%s]\n", cmd.arg);
	ft_dprintf(STDIN_FILENO, "%d\n", ret);
	if (ret == -1)
		invalid_cmd(cmd);
	return (0);
}