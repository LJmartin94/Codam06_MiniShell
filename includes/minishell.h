/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 12:02:24 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/15 17:30:58 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum	s_composition_type
{
	separator,
	command,
	option,
	arg
}				t_composition_type;

typedef struct	s_icomp
{
	char	*sep;
	char	*cmd;
	char	*opt;
	char	*arg;
	s_icomp	*next;
}				t_icomp;

void	parse_input(const char *input);

#endif
