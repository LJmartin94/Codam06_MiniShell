/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 11:59:41 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/19 18:09:11 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"

// #include<stdio.h>
#include<signal.h>
// #include<unistd.h>

void sig_handler(int signo)  //TODO: SIGQUIT ctrl-(esc)
{
	if (signo == SIGINT)
    	ft_printf("received SIGINT\n");
	if (execve("minishell", NULL, NULL) == -1)//TODO: remember to pass this the current env, make sure to call in correct dir
	{
		ft_printf("execve died\n");
	}
}

void	get_input(void)
{
	char *buf;
	int ret;

	write(1, "\U0001F40C", 4);
	write(1, " ", 1);
	ret = get_next_line(STDIN_FILENO, &buf);
	// ret = read(0, &buf, 1);
	if (ret == 0)	//ctrl-D
	{
		ft_printf("\n"); //TODO: try not to print ^D
		exit(0);
	}
	parse_input(buf);
}

int		main(void)
{
	// void (*f)(int);
	// char buf[1];
	while (1)
	{

		signal(SIGINT, sig_handler); //catches signals ONLY WORKS IN MAIN THREAD
		get_input();
	}
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