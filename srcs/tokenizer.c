/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 11:38:56 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/19 18:53:31 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "token_table.h"

int		recognize_special_char(char *input, int j)
{
	int i;

	i = 0;
	while (i < token_table_size)
	{
		if (ft_strncmp(input + j, g_token_table[i].token, g_token_table[i].len) == 0)
			return (g_token_table[i].len);
		i++;
	}
	return (0);
}

void	separate_special_char(char *input, t_token **head, int *j, int *k)
{
	int		len;
	t_token	*token;

	len = recognize_special_char(input, *j);
	if (len > 0)
	{
		token = create_token(input, *k, *j - *k);
		if (token != NULL)
			add_token(head, token);
		token = create_token(input, *j, len);
		if (token != NULL)
			add_token(head, token);
		*k = *j + len;
		*j = *j + len - 1;
	}
}

void	tokenize_string(char *input, t_token **head)
{
	int		j;
	int		k;
	t_token	*token;

	j = 0;
	k = 0;
	token = NULL;
	while (input[j] != '\0')
	{
		separate_special_char(input, head, &j, &k);
		if (input[j + 1] == '\0')
		{
			token = create_token(input, k, ft_strlen(input + k));
			if (token != NULL)
				add_token(head, token);
		}
		j++;
	}
}

t_token *validate_tokens(char **input) 
{
	int		i;
	t_token	*head;

	i = 0;
	head = NULL;
	while (input[i] != NULL)
	{
		tokenize_string(input[i], &head);
		i++;
	}
	return (head);
}

void print_tokens(t_token **tokens) //
{
	t_token *cur;
	cur = *tokens;
	ft_printf("print tokens:\n");
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
