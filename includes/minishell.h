/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 12:02:24 by jsaariko      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/10/16 15:05:57 by jsaariko      ########   odam.nl         */
=======
/*   Updated: 2020/10/15 18:39:20 by limartin      ########   odam.nl         */
>>>>>>> 15 October 2020, Made a lot of changes to allow the project to compile.
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

<<<<<<< HEAD
=======
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

>>>>>>> 15 October 2020, Made a lot of changes to allow the project to compile.
void	parse_input(const char *input);

#endif
