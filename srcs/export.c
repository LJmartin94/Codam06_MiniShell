/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 09:39:24 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/29 09:39:32 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

static int	validate_env(char *env_str)
{
	int i;

	i = 0;
	if (ft_isalpha(env_str[i]) == 0)
		return (-1);
	while (env_str[i] != '\0')
	{
		if (env_str[i] == '=')
			break ;
		i++;
	}
	if (env_str[i] == '\0')
		return(0);
	if (env_str[i] == '=' && env_str[i + 1] == '\0') //exports
		return(1);
	return (1);
}

int			ft_export(t_vector *env, t_icomp *cmd) //TODO: Export with nothing as param prints all items with declare -x in front?
{
	t_env *item;
	int ret;

	ret = validate_env(cmd->arg);
	if (ret == -1)
	{
		ft_dprintf(STDERR_FILENO, "export: '%s': not a valid identifier\n", cmd->arg);
		return (0);
	}
	if (ret == 0)
		return (0);
	item = get_env_item(cmd->arg);
	if (item == NULL)
		return (0);
	ret = vector_push(env, item);
	if (!ret)
		error_exit_errno();
	return (0);
}
