/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 14:04:54 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/15 18:04:15 by limartin      ########   odam.nl         */
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
void	manage_fsm(t_token *tokens);

#endif