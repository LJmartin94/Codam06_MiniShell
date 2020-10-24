/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/15 11:54:53 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/10/24 20:10:39 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "error.h"

void	free_tokens(t_token *head)
{
	t_token *tmp;

	while (head)
	{
		tmp = head->next;
		free(head->token);
		head->token = NULL;
		free(head);
		head = tmp;
	}
}

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
		cur = cur->next;
	cur->next = token;
}

t_token	*create_token(const char *tokens, int pos, size_t len)
{
	t_token	*token;
	char	*token_str;
	int		k;

	if (len == 0)
		return (NULL);
	token = (t_token *)e_malloc(sizeof(t_token));
	k = 0;
	token_str = (char *)e_malloc(sizeof(char) * (len + 1));
	ft_strlcpy(token_str, tokens + pos, len + 1);
	token->token = token_str;
	token->next = NULL;
	return (token);
}
