/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 14:04:54 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/19 18:15:53 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>

typedef struct		s_token
{
	char			*token;
	struct s_token	*next;
}					t_token;

t_token				*get_tokens(const char *input);
void				add_token(t_token **head, t_token *token);
t_token				*create_token(char *tokens, int j, size_t len);
void				free_matrix(char **tokens);
void				print_tokens(t_token **tokens);
void				parse_input(const char *input);

#endif
