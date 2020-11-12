/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage_execution.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 16:06:45 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/12 10:55:49 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

void	run_command(t_cmd f, t_vector *env, t_icomp *comp)
{
	char *path;
	char **envp;
	char **argv;

	if (f != NULL)
		f(env, comp, STDOUT_FILENO);
	else
	{
		path = find_path(env, comp);
		if (path == NULL)
		{
			invalid_cmd(comp);
			exit(0);
		}
		envp = env_to_envp(env);
		free_env(env);
		argv = build_argv(comp);
		execve(path, argv, envp);
	}
	exit(0);
}

/*
** //TODO: Make sure this is killed even when doing ctrl-c
** //TODO: what to do if index not found?
*/

// void	finish_process(int index)
// {
// 	t_process *pid_item;
// 	int wstatus;

// 	pid_item = vector_get(&g_pid_list, index);
// 	if (pid_item == NULL)
// 		return ;
// 	waitpid(pid_item->pid, &wstatus, 0);
		
// 	e_close(pid_item->fd);
// 	g_ret_val = WEXITSTATUS(wstatus);
// 	// ft_dprintf(STDOUT_FILENO, "ret val: %d\n", g_ret_val);
// 	free(pid_item);
// 	vector_delete(&g_pid_list, index);
// }

#include <sys/types.h>//
#include <signal.h>//

t_process	*parent_process(t_icomp *comp, int pid, int fd[2], t_process *prev) //TODO: still doesn't always kill processess properly
{
	// t_process	*pid_malloc;
	// int			item_index;

	// e_close(fd[1]);
	// pid_malloc = (t_process *)e_malloc(sizeof(t_process));
	// pid_malloc->pid = pid;
	// pid_malloc->fd = fd[0];
	// vector_push(&g_pid_list, pid_malloc);
	// if (ft_strncmp(comp->sep, "|", 2) != 0)
	// {
	// 	if (stdin == -1)
	// 	{
	// 		item_index = vector_search(&g_pid_list, cmp_pid, pid_malloc);
	// 		while (g_pid_list.amt > 0)
	// 			finish_process(0);
	// 		// if (item_index >= 0)
	// 			// finish_process(item_index);
	// 		// else
	// 			// ft_dprintf(STDOUT_FILENO, "fuck, g_pid_list is fucked\n");
	// 	}
	// 	else
	// 	{
	// 		while (g_pid_list.amt > 0)
	// 			finish_process(0);
	// 	}
	// }

		//parent process doesn't need to write? 
	e_close(fd[1]);
	t_process *pid_malloc;
	// int item_index;


	pid_malloc = (t_process *)e_malloc(sizeof(t_process));
	pid_malloc->pid = pid;
	//parent process needs to store read end of pipe
	pid_malloc->fd = fd[0];
	vector_push(&g_pid_list, pid_malloc);
	//TODO: Rn so many processes are left uncleared
	

	// if (stdin != -1 && ft_strncmp(comp->sep, "|", 2) != 0)// if there's stdin, but no following pipe
	// {
	// 	while (g_pid_list.amt > 0)
	// 	{
	// 		finish_process(g_pid_list.amt - 1); //TODO: Should I finish all processes from before, or is it possible to have some background process still running
	// 	}
	// }
	// else if (stdin == -1 && ft_strncmp(comp->sep, "|", 2) != 0) //if there isn't stdin nor pipe, current process should just die
	// {
	// 	item_index = vector_search(&g_pid_list, cmp_pid, pid_malloc);
	// 	if (item_index >= 0)
	// 		finish_process(item_index);
	// 	else
	// 		ft_dprintf(STDOUT_FILENO, "fuck, g_pid_list is fucked\n");
	// }

	int wstatus;
	// vector_debug(STDOUT_FILENO, &g_pid_list, pid_print);
	if (ft_strncmp(comp->sep, "|", 2) != 0)//if no piped output
	{
		//wait for process, close fd
		waitpid(pid, &wstatus, 0);
		e_close(pid_malloc->fd);
		vector_delete(&g_pid_list, vector_search(&g_pid_list, cmp_pid, pid_malloc));
		free(pid_malloc);
		pid_malloc = NULL;
	}
	else// if there is piped output
	{
		//do not wait for process or close fd
	}
	if (prev != NULL)// if there is piped input
	{
		// int ind = vector_search(&g_pid_list, cmp_pid, pid_malloc);
		// ft_dprintf(STDOUT_FILENO, "index: %d\n", ind);
		// t_process *prev = (t_process *)vector_get(&g_pid_list, ind - 1);
		// if (prev != NULL)
		// {
			// ft_dprintf(STDOUT_FILENO, "stdin %d == prev->fd %d\n", stdin, prev->fd);
			e_close(prev->fd);
			waitpid(prev->pid, NULL, 0);
			vector_delete(&g_pid_list, vector_search(&g_pid_list, cmp_pid, prev));
			free(prev);
			prev = NULL;
		// }
		// else
		// {
			// ft_dprintf(STDOUT_FILENO, "something wrong\n");
		// }
		
		//close previous fd
	}
	else// if there is no piped input
	{
		//do not close previous fd
	}
	return (pid_malloc);	
}

#include "fcntl.h"//
//I dont think any of these accept <, but they still run it and cry if it's not a valid file
int		redirect_builtin(t_icomp *comp)
{
	int fd;

	fd = STDOUT_FILENO;
	if (ft_strncmp(comp->sep, ">>", 3) == 0) //creates if doesn't exist, appends
		fd = open(comp->right->cmd, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (ft_strncmp(comp->sep, ">", 2) == 0)
		fd = open(comp->right->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (ft_strncmp(comp->sep, "<", 2) == 0)//returns where to read from
	{
		fd = open(comp->right->cmd, O_RDONLY, 0666);
		if (fd == -1)
			ft_dprintf(STDERR_FILENO, "oops, no such file");//solidify error checking
		else
			close(fd);
		fd = STDOUT_FILENO; //write to
	}
	return (fd);
}

void	exec_builtin(t_cmd f,t_vector *env, t_icomp *comp)
{
	//handle builtin redirections
	int fd = redirect_builtin(comp);
	f(env, comp, fd); //TODO: store return value in g_ret_val ????
}

t_process	*exec_command(t_vector *env, t_icomp *comp, t_process *process)
{
	t_cmd	f;
	int		pid;
	int		fd[2];

	// t_process *process = NU;
	fd[0] = -1;
	fd[1] = -1;
	if (ft_strncmp(comp->sep, "|", 2) == 0)
	{
		if (pipe(fd) == -1)
			error_exit_errno();
	}
	f = get_command(comp);
	if (f != NULL && ft_strncmp(comp->sep, "|", 2) != 0 && process == NULL)
		exec_builtin(f, env, comp);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			handle_redirections(comp, fd, process);
			run_command(f, env, comp);
		}
		else
			process = parent_process(comp, pid, fd, process);
	}
	return (process);
}


//builtins aren't redirected in a fork, but within the commands