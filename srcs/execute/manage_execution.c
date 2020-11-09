/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage_execution.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 16:06:45 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/09 11:11:12 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

void	run_command(t_cmd f, t_vector *env, t_icomp *comp, int fd[2])
{
	char *path;
	char **envp;
	char **argv;

	handle_redirections(comp, fd);
	if (f != NULL)
		f(env, comp);
	else
	{
		path = find_path(env, comp);
		if (path == NULL)
		{
			invalid_cmd(comp);
			exit(0);
		}
		envp = env_to_envp(env);
		free_environment(env);
		argv = build_argv(comp);
		// ft_dprintf(STDOUT_FILENO, "executing...\n");
		execve(path, argv, envp);
	}
	exit(0);
}

void	finish_process(int index)
{
	t_process *pid_item;

	//TODO: Make sure this is killed even when doing ctrl-c
	// ft_dprintf(STDOUT_FILENO, "list index: %d\n", index);
	pid_item = vector_get(&g_pid_list, index);
	if (pid_item == NULL)//TODO: what to do if index not found?
		return ;
	// ft_dprintf(STDOUT_FILENO, "index: %d closing process %d, fd: %d\n", index, pid_item->pid, pid_item->fd);
	// ft_dprintf(STDOUT_FILENO, "waitingg..\n\n");
	e_close(pid_item->fd);
	waitpid(pid_item->pid, NULL, 0);
	// vector_debug(STDOUT_FILENO, &g_pid_list, pid_print);
	// ft_dprintf(STDOUT_FILENO, "waited..\n\n");
	free(pid_item);
	vector_delete(&g_pid_list, index);
}

//infinite processes should wait for 


//TODO: build something that stores open fd with the pid
void	parent_process(t_icomp *comp, int pid, int fd[2], int stdin)
{
	//parent process doesn't need to write? 
	e_close(fd[1]);
	t_process *pid_malloc;
	int item_index;


	pid_malloc = (t_process *)e_malloc(sizeof(t_process));
	pid_malloc->pid = pid;
	//parent process needs to store read end of pipe
	pid_malloc->fd = fd[0];
	vector_push(&g_pid_list, pid_malloc);
	//TODO: Rn so many processes are left uncleared
	

	if (stdin != -1 && ft_strncmp(comp->sep, "|", 2) != 0)
	{
		while (g_pid_list.amt > 0)
		{
			finish_process(0); //TODO: Should I finish all processes from before, or is it possible to have some background process still running
		}
	}
	else if (stdin == -1 && ft_strncmp(comp->sep, "|", 2) != 0)
	{
		item_index = vector_search(&g_pid_list, cmp_pid, pid_malloc);
		if (item_index >= 0)
			finish_process(item_index);
		else
			ft_dprintf(STDOUT_FILENO, "fuck, g_pid_list is fucked\n");
	}
}

int		exec_command(t_vector *env, t_icomp *comp, int stdin)
{
	//TODO: ??
	int		pid;
	t_cmd	f;
	int		fd[2];

	fd[0] = -1;//read end
	fd[1] = -1;//write end


	if (ft_strncmp(comp->sep, "|", 2) == 0)
	{
		if (pipe(fd) == -1)
			error_exit_errno();
	}
	f = get_command(comp);
	pid = fork();
	if (pid == 0)
	{
		if (stdin != -1)
		{
			dup2(stdin, STDIN_FILENO);
			e_close(stdin);
		}
		run_command(f, env, comp, fd); //TODO: if prev is invalid command, don't do second part
	}
	else 
		parent_process(comp, pid, fd, stdin);
	return (fd[0]);
}
