/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 12:51:50 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/08 14:34:44 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

static t_env	*expand_find(t_vector *env, char *pos)
{
	int		len;
	char	*key;
	int		index;
	t_env	*item;

	len = 0;
	while (ft_isalnum(pos[len]) || pos[len] == '_')
		len++;
	key = (char *)e_malloc(sizeof(char) * len + 1);
	key = ft_memcpy(key, pos, sizeof(char) * len);
	index = vector_search(env, compare_key, key);
	item = vector_get(env, index);
	if (item == NULL)
	{
		item = (t_env *)e_malloc(sizeof(t_env));
		item->key = key;
		item->value = ft_strdup("");
	}
	else
		free(key);
	return (item);
}

static void		expand_env_variable(t_vector *env, char **str, size_t *i)
{
	t_env	*replace;
	char	*final;

	final = NULL;
	replace = expand_find(env, (*str) + *i + 1);
	if (replace->value == NULL)
		replace->value = ft_strdup("");
	final = ft_strsplice((*str), *i,
		ft_strlen(replace->key) + 1, replace->value);
	if (!final)
		error_exit_errno();
	free(*str);
	(*str) = final;
	*i = *i + ft_strlen(replace->value) - 1;
}

static void		replace_arg(t_vector *env, char **str, size_t *i, t_quotes q)
{
	char	*final;

	final = NULL;
	if ((*str)[*i + 1] == '?')
	{
		final = ft_strsplice((*str), *i, 2, ft_itoa(g_ret_val));
		if (!final)
			error_exit_errno();
		free(*str);
		(*str) = final;
		i += 2;
	}
	else if (((*str)[*i + 1] == '"' && q.dquote % 2 == 0) ||
			((*str)[*i + 1] == '\'' && q.quote % 2 == 0) ||
			(*str)[*i + 1] == '_' || (*str)[*i + 1] == '*' ||
			ft_isalnum((*str)[*i + 1]))
	{
		expand_env_variable(env, str, i);
	}
	else
		(*i)++;
}

static void		quotes(char c, int *quote, int *dquote)
{
	if (c == '"')
	{
		if ((*quote) % 2 == 0)
			((*dquote))++;
		else
			((*dquote))--;
	}
	else if (c == '\'')
	{
		if ((*dquote) % 2 == 0)
			(*quote)++;
		else
			(*quote)--;
	}
}

void			expand_env(t_vector *env, char **str)
{
	size_t		i;
	t_quotes	q;
	int			esc;

	i = 0;
	q.quote = 0;
	q.dquote = 0;
	esc = 0;
	while ((*str)[i] != '\0')
	{
		quotes((*str)[i], &q.quote, &q.dquote);
		if ((*str)[i] == '$' && q.quote % 2 == 0 && esc % 2 == 0)
			replace_arg(env, str, &i, q);
		else
			i++;
		if (i - 1 > 0)
		{
			if ((*str)[i - 1] == '\\')
				esc++;
			if ((*str)[i - 1] != '\\')
				esc = 0;
		}
	}
}
