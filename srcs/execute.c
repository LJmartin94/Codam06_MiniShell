/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 16:32:46 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/28 12:11:38 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
** TODO: Build command validators in functions
*/

typedef int(*cmd)(t_vector *, t_icomp);

cmd		get_command(t_icomp comp)
{
	if (comp.cmd == NULL)
		return (NULL);
	if (ft_strncmp(comp.cmd, "env", 4) == 0)
		return (ft_env);
	if (ft_strncmp(comp.cmd, "unset", 6) == 0)
		return (ft_unset);
	if (ft_strncmp(comp.cmd, "export", 7) == 0)
		return (ft_export);
	if (ft_strncmp(comp.cmd, "echo", 5) == 0)
		return (ft_echo);
	if (ft_strncmp(comp.cmd, "pwd", 4) == 0)
		return (ft_pwd);
	if (ft_strncmp(comp.cmd, "cd", 3) == 0)
		return (ft_cd);
	if (ft_strncmp(comp.cmd, "exit", 5) == 0)
		return (ft_exit);
	ft_dprintf(STDIN_FILENO, "lol\n");
	return (NULL);
}

void	execute(t_vector *env, t_icomp comp)
{
	cmd f;

	/*
The main process (e.g. bash) forks itself using the fork glibc wrapper
	
The forked process sees that output redirection was entered on the command line and opens the specified file using the open(2)

The forked process calls dup2 to copy the freshly opened file descriptor over stdin/stdout/stderr
The forked process closes the original file handler to avoid resource leaks

The forked process proceeds as normal by calling the execve(2) syscall or something similar to replace the executable image with that of the process to be run (e.g. ls)


    char *argv[] = { "/bin/ls", "-la", 0 };
    char *envp[] =
    {
        "HOME=/",
        "PATH=/bin:/usr/bin",
        "USER=brandon",
        0
    };
    int fd = open("/home/brandon/ls.log", O_WRONLY|O_CREAT|O_TRUNC, 0666);
    dup2(fd, 1); // stdout is file descriptor 1
    close(fd);
    execve(argv[0], &argv[0], envp);
    fprintf(stderr, "Oops!\n");
    return -1;


	*/

	// How bash works: main process forks
	//Iterate through items. If pipe, open pipe, fork command and write result from one process, read from other. Same with redirections. Always add process to g_pid
	f = get_command(comp);
	if (f == NULL)
		invalid_cmd(comp);
	else
		f(env, comp);
}
