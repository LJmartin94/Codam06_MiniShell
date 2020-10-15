/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 14:04:54 by jsaariko      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/10/16 14:49:36 by jsaariko      ########   odam.nl         */
=======
/*   Updated: 2020/10/15 18:04:15 by limartin      ########   odam.nl         */
>>>>>>> 15 October 2020, Made a lot of changes to allow the project to compile.
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>//

typedef struct	s_token
{
	char *token;
	struct s_token *next;
}				t_token;

t_token	*get_tokens(const char *input);
void	add_token(t_token **head, t_token *token);
t_token	*create_token(char *tokens, int j, size_t len);
void	free_matrix(char **tokens);
<<<<<<< HEAD
void	parse_input(const char *input);

=======
void	manage_fsm(t_token *tokens);
>>>>>>> 15 October 2020, Made a lot of changes to allow the project to compile.

#endif