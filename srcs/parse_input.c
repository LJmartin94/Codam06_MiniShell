/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 12:04:04 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/14 18:08:00 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"//
// #include "fsm.h"//
#include "parser.h"

void	add_token(t_token **head, t_token *token)
{
	t_token *cur;

	if (*head == NULL)
	{
		*head = token;
		return ;
	}
	cur = *head;
	while (cur->next != NULL)
	{
		// ft_printf("cur %p, cur->next %p, infinite looooop\n");
		cur = cur->next;
	}
	cur->next = token;
}

t_token	*create_token(char **tokens, int i, int j, size_t len)
{
	t_token *token;
	char *token_str;
	int k;

	token = (t_token *)malloc(sizeof(t_token));
	k = 0;
	token_str = (char *)malloc(sizeof(char) * (len + 1));
	ft_strlcpy(token_str, tokens[i] + j, len + 1);
	token->token = token_str;
	token->next = NULL;
	return (token);
}

// for some reason when I allocate a token, it doesn't assign next to null
t_token	*validate_tokens(char **tokens) //logic here doesn't work. Need to tokenize entire parts until you hit special character
{
	int i;
	int j;
	t_token *head;
	t_token *token;

	head = NULL;
	i = 0;
	j = 0;
	while (tokens[i] != NULL)
	{
		// while (tokens[i][j] != '\0')
		// {
			// if (tokens[i][j] == 34 || tokens[i][j] == 39)
			// {
				// token = create_token(tokens, i, j, 1);
				// add_token(&head, token);
			// }
			// j++;
		// }
		j = 0;
		token = create_token(tokens, i, j, ft_strlen(tokens[i] + j));
		add_token(&head, token);
		i++;
	}
	return (head);
}

void print_tokens(t_token **tokens)
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
	char **tokens;
	t_token *validated_tokens;

	tokens = ft_split(input, ' ');
	validated_tokens = validate_tokens(tokens);
	print_tokens(&validated_tokens);
	//free tokens
	return (validated_tokens);
}

void	parse_input(const char *input)
{
	t_token *tokens;
	tokens = get_tokens(input);
	// manage_fsm(input);

	ft_printf("%s\n", input);
}
