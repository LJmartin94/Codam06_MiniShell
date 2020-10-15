/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 12:02:24 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/15 18:39:20 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//we may not even need these
typedef enum	s_composition_type
{
	type_separator,
	type_command,
	type_option,
	type_arg
}				t_composition_type;

typedef struct	s_icomp
{
	char			*sep;
	char			*cmd;
	char			*opt;
	char			*arg;
	struct s_icomp	*next;
}				t_icomp;

void	parse_input(const char *input);

#endif
