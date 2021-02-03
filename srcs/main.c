/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/02/03 16:57:00 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"
#include "execute.h"
#include <signal.h>

static void	parse_and_execute(t_vector *env, char **str, t_icomp *comp)
{
	int		no_error;

	no_error = 1;
	expand_env(env, str);
	parse_input(*str, comp);
	no_error = no_syntax_errors(comp);
	if (no_error)
		execute(env, comp);
	free_components(comp);
}

int			run_shell(t_vector *env, char *buf)
{
	char	**split;
	t_icomp	comp_blocks;
	size_t	i;
	int		no_error;
	t_icomp error;

	i = 0;
	split = split_unless_quote(buf, ';');
	no_error = 1;
	parse_input(buf, &error);
	no_error = no_syntax_errors(&error);
	free_components(&error);
	while (split[i] != NULL && no_error)
	{
		parse_and_execute(env, &(split[i]), &comp_blocks);
		i++;
	}
	free_matrix(split);
	return (no_error);
}

char		*g_cmd_line;

int			create_cmd_line()
{
	char	*buf;
	int		ret;
	char	*other;

	other = NULL;
	if (g_cmd_line == NULL)
		e_write(STDOUT_FILENO, "\U0001F40C ", 6);
	ret = get_next_line(STDIN_FILENO, &buf);
	if (g_cmd_line == NULL && ft_strcmp(buf, "\0", 1) == 0)
		other = NULL;
	else if (g_cmd_line == NULL)
		other = ft_strdup(buf);
	else
		other = ft_strjoin(g_cmd_line, buf);
	free(buf);
	free(g_cmd_line);
	g_cmd_line = other;
	return (ret);
}

int			get_input(t_vector *env)
{
	int ret;

	ret = create_cmd_line();
	if (ret == 0)
	{
		if (g_cmd_line == NULL)
		{
			e_write(STDOUT_FILENO, "\n", 1);
			exit(g_ret_val);
		}
		return (ret);
	}
	if (ret < 0)
		error_exit_msg(C_GNL_FAIL, E_GNL_FAIL);
	if (g_cmd_line == NULL)
		g_cmd_line = ft_strdup("");
	run_shell(env, g_cmd_line);
	free(g_cmd_line);
	g_cmd_line = NULL;
	return (ret);
}

int			main(int ac, char **av, char **envp)
{
	t_vector	*env;

	g_cmd_line = NULL;
	g_pwd = getcwd(g_pwd, 0);
	if (g_pwd == NULL)
		error_exit_msg(1, "Invalid location in file structure\n");
	g_ret_val = 0;
	g_amt_processes = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	env = init_env(envp);
	(void)ac;
	(void)av;
	while (1)
		get_input(env);
	return (0);
}
