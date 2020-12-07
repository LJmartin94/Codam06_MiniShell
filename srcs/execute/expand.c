/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 12:51:50 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/07 18:23:49 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

/*
** //TODO: Make work with multiple args
*/

static t_env	*expand_find(t_vector *env, char *pos)
{
	int		len;
	char	*key;
	int		index;
	t_env	*item;

	len = 0;
	while (ft_isalnum(pos[len]) || pos[len] == '_')
		len++;
	if (len >= 0)
	{
		key = (char *)e_malloc(sizeof(char) * len + 1);
		key = ft_memcpy(key, pos, sizeof(char) * len);
	}
	else
		key = ft_strdup(pos);
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

static void		replace_arg(t_vector *env, char **str, size_t *i, int quote, int dquote)
{
	char	*final;
	t_env	*replace;

	final = NULL;
	if ((*str)[*i + 1] == '?')
	{
		final = ft_strsplice((*str), *i, 2, ft_itoa(g_ret_val));
		free(*str);
		(*str) = final;
		i += 2;
	}
	else if (((*str)[*i + 1] == '"' && dquote % 2 == 0) ||
			((*str)[*i + 1] == '\'' && quote % 2 == 0) ||
			(*str)[*i + 1] == '_' || (*str)[*i + 1] == '*' ||
			ft_isalnum((*str)[*i + 1]))
	{
		replace = expand_find(env, (*str) + *i + 1);
		if (replace->value == NULL)
			replace->value = ft_strdup("");
		final = ft_strsplice((*str), *i, ft_strlen(replace->key) + 1, replace->value);
		free(*str);
		(*str) = final;
		*i = *i + ft_strlen(replace->value) - 1;
	}
	else
		(*i)++;
}

/*
** //TODO: I think expansions work correctly but god it's so horrible,
**		please test this properly
*/

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
	size_t	i;
	int		quote;
	int		dquote;
	int		esc;

	i = 0;
	quote = 0;
	dquote = 0;
	esc = 0;
	while ((*str)[i] != '\0')
	{
		quotes((*str)[i], &quote, &dquote);
		if ((*str)[i] == '$' && quote % 2 == 0 && esc % 2 == 0)
			replace_arg(env, str, &i, quote, dquote);
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
