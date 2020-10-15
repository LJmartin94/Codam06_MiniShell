/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 11:38:56 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/15 12:04:20 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"

void	handle_special_char(t_token **head, char *tokens, int j, int k)
{
	t_token *token;

	token = NULL;
	token = create_token(tokens, k, (ft_strlen(tokens + k) - (ft_strlen(tokens) - j)));
	if (token != NULL)
		add_token(head, token);
	token = create_token(tokens, j, 1);
	if (token != NULL)
		add_token(head, token);
}

void	tokenize_string(char *tokens, t_token **head)
{
	int j;
	int k;
	t_token *token;

	j = 0;
	k = 0;
	token = NULL;
	while (tokens[j] != '\0')
	{
		if (tokens[j] == 34 || tokens[j] == 39)
		{
			handle_special_char(head, tokens, j, k);
			k = j + 1;
		}
		if (tokens[j + 1] == '\0')
		{
			token = create_token(tokens, k, ft_strlen(tokens + k));
			if (token != NULL)
				add_token(head, token);
		}
		j++;
	}
}

t_token *validate_tokens(char **tokens)
{
	int i;
	t_token *head;
	t_token *token;

	i = 0;
	head = NULL;
	token = NULL;
	while (tokens[i] != NULL)
	{
		tokenize_string(tokens[i], &head);
		i++;
	}
	return (head);
}

void print_tokens(t_token **tokens) //
{
	t_token *cur;
	cur = *tokens;
	while (cur != NULL)
	{
		ft_printf("%p, [%s]\n", cur, cur->token);
		cur = cur->next;
	}
}

t_token	*get_tokens(const char *input)
{
	char **split_input;
	t_token *validated_tokens;

	split_input = ft_split(input, ' ');
	validated_tokens = validate_tokens(split_input);
	print_tokens(&validated_tokens);
	free_matrix(split_input);
	return (validated_tokens);
}