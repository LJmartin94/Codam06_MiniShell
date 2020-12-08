/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 12:14:43 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/08 12:15:03 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		e_write(STDOUT_FILENO, "\n", 1);
		if (g_pid_list.amt == 0)
		{
			e_write(STDOUT_FILENO, "\U0001F40C ", 6);
		}
	}
}

void	handle_sigquit(int signo)
{
	if (signo == SIGQUIT)
	{
		if (g_pid_list.amt != 0)
			e_write(STDOUT_FILENO, "Quit: \n", 7);
	}
}
