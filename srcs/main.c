/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/20 16:23:58 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"

// #include<stdio.h>
#include<signal.h>
// #include<unistd.h>


int sign;



void sig_handler(int signo)  //TODO: SIGQUIT ctrl-(esc)
{
	ft_printf("sig_handler: sign: %d\n", sign);
	sign = 1;
	ft_printf("sig_handler: sign: %d\n", sign);
	if (signo == SIGINT)
    	ft_printf("received SIGINT\n");
	// if (execve("minishell", NULL, NULL) == -1)//TODO: remember to pass this the current env, make sure to call in correct dir
	// {
		// ft_printf("execve died\n");
	// }
	// signal(SIGINT, sig_handler);
	kill(0, SIGINT);
	return ;
}

// static void		kill_processes(int signal)
// {
	// size_t		i;
	// pid_t		process;

	// i = 0;
	// while (i < g_pid.index)
	// {
		// vec_get(&g_pid, &process, i);
		// kill(process, signal);
		// i++;
	// }
	// if (g_pid.index)
		// ft_printf("\n");
	// else
		// ft_printf("\n%s", g_prompt);
// }

// void			sighandler(int signal)
// {
	// if (g_pid.index == 0 && signal != SIGQUIT)
	// {
		// g_siggy += 1;
	// }
	// kill_processes(signal);
// }


void	get_input(void)
{
	char *buf;
	int ret;

	write(1, "\U0001F40C", 4);
	write(1, " ", 1);
	sign = 7;
	ret = get_next_line(STDIN_FILENO, &buf);
	// ret = read(0, &buf, 1);
	if (ret == 0)	//ctrl-D
	{
		ft_printf("\n"); //TODO: try not to print ^D
		exit(0);
	}
	parse_input(buf);
}

int lol()
{
	while (1)
	{
		if (sign == 1)
			ft_printf("wooooooo!!!!!\n");
		ft_printf("sign: %d\n", sign);
		get_input();
	}
}

void my_program()
{
	ft_printf("this is the child\n");
	while(1)
	{
		;
	}
}

int		main(void)
{
	// void (*f)(int);
	// char buf[1];
	sign = 0;

	// int pid = fork(); //TODO: Possibly fork into main that just listens and a child that runs program and can be killed
	// if (pid == 0)
		// my_program();
	// else
	// {
		// signal(SIGINT, sig_handler);
		// while(1);
	// }
	
	// int pid = getpid();
	// ft_printf("%d\n", pid);
	// signal(SIGINT, sig_handler); //catches signals ONLY WORKS IN MAIN THREAD
	
	return (0);
}



// void sig_handler(int signo)
// {
//   if (signo == SIGINT)
//     printf("received SIGINT\n");
// }

// int main(void)
// {
//   if (signal(SIGINT, sig_handler) == SIG_ERR)
//   printf("\ncan't catch SIGINT\n");
//   // A long long wait so that we can easily issue a signal to this process
//   while(1) 
//     sleep(1);
//   return 0;
// }