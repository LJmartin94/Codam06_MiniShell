/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 09:39:24 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/27 10:00:09 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

static int	validate_env(char *env_str)
{
	int i;

	i = 0;
	if (env_str[i] == '=')
		return (-1);
	while (env_str[i] != '\0')
	{
		if (env_str[i] == '=')
			break ;
		i++;
	}
	if (env_str[i + 1] == '\0')
		return(0);
	return (1);
}

int			ft_export(t_vector *env, t_icomp cmd)
{
	t_env *item;
	int ret;

	ret = validate_env(cmd.arg);
	if (ret == -1)
	{
		ft_dprintf(STDERR_FILENO, "Export: '%s': not a valid identifier", cmd.arg); //turn into actual error msg that quits the thing
		return (0);
	}
	item = get_env_item(cmd.arg);
	if (item == NULL)
		return (0);
	ret = vector_push(env, item);
	if (!ret)
		error_exit_errno();
	return (0);
}
